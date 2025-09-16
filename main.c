#include <stdlib.h>
#include <raylib.h>
#include <gamemenu.h>
#include <gamewindow.h>

int main()
{
    InitWindow(1200, 625, "Blackjack");
    SetTargetFPS(60);

    int isOnline = StartMenu(); //StartMenu returns if player is logged in or not and eventual errors

    if(isOnline == -1)
    {
        exit(-1);
    }
    else
    {
        int retry = 0;
        
        do
        {
            retry = GameStart(isOnline);
        } while (retry);
    }

}