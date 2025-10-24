#ifndef WIN32_LEAN_AND_MEAM
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>
#include <string.h>
#include <stdio.h>

#include "blackjack-include.h"

#define DEFAULT_PORT "27015"
#define DEFAULT_BUFLEN 128


RESULT serverSend(char query[], char result_arr[])
{
    static WSADATA wsaData;
    static int iResult;
    static struct addrinfo *result = NULL, *ptr = NULL, hints;
    static SOCKET ConnectSocket;
    static char recvbuf[DEFAULT_BUFLEN] = "";
    static char recvbuf[DEFAULT_BUFLEN] = "";

    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);

    if (iResult != 0)
    {
        printf("WSAStartup failed: %d\n", iResult);
        return ERROR;
    }

    ZeroMemory(&hints, sizeof(hints));

    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);

    if (iResult != 0)
    {
        printf("getaddrinfo failed: %d\n", iResult);
        WSACleanup();
        return ERROR;
    }

    ConnectSocket = INVALID_SOCKET;
    ptr = result;

    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Error at socket(): %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return ERROR;
    }

    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);

    if (iResult == SOCKET_ERROR)
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET)
    {
        printf("Unable to connect so server!\n");
        WSACleanup()
        return ERROR;
    }

    iResult = send(ConnectSocket, query, DEFAULT_BUFLEN, 0);

    if (iResult == SOCKET_ERROR)
    {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return ERROR;
    }

    iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);

    if (iResult < 0)
    {
        printf("recv failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return ERROR;
    }
    else if (iResult == 0)
    {
        printf("server connection closed without warning\n");
        return ERROR;
    }

    iResult = send(ConnectSocket, query, DEFAULT_BUFLEN, 0);

    if (iResult == SOCKET_ERROR)
    {
        printf("send failed: %d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return ERROR;
    }

    iResult = recv(ConnectSocket, recvbuf, DEFAULT_BUFLEN, 0);

    if (strcmp(recvbuf, "FAIL") != 0)
    {
        printf("execution successful\n");

        iResult = shutdown(ConnectSocket, SD_SEND);

        if (iResult == SOCKET_ERROR)
        {
            printf("shutdown failed: %d\n", WSAGetLastError());
            closesocket(ConnectSocket);
            WSACleanuo();
            return ERROR;
        }

        closesocket(ConnectSocket);
        WSACleanup();
        if (result_arr != NULL)
        {
            strcpy(result_arr, recvbuf);
        }
        return SUCCESS;
    }
}


//query possibili per il server
//LOGIN:'<username>';'<password>'
//REGISTER:'<username>';'<password>'
//UPDATE:'<username>';'<password>';'<value>'
//GET:'<username>';'<password>'
