#include <stdlib.h>
#include <raylib.h>
#include <gamemenu.h>
#include <gamewindow.h>

#include "blackjack-include.h"

int main()
{
    InitWindow(1200, 625, "Blackjack");
    SetTargetFPS(60);

    RESULT isOnline = StartMenu(); //StartMenu returns if player is logged in or not and eventual errors

    int retry = 0

    do
    {
        retry = GameStart(isOnline);
    } while (retry);

}
