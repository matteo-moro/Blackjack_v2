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

//uso variabili globali per non creare nuove variabili ogni volta che mando un query
//TODO: generalizzare la libreria per avere qualcosa di riusabile

WSADATA wsaData;
int iResult;
struct addrinfo *result = NULL, *ptr = NULL, hints;
SOCKET ConnectSocket;
char qbuffer[DEFAULT_BUFLEN] = "";
char recvbuf[DEFAULT_BUFLEN] = "";
int initResult;


RESULT serverSend(char query[])
{
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
}