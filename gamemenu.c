#include <stdlib.h>
#include <raylib.h>
#include <raygui.h>
#include <string.h>

#include "gamemenu-structs.h"
//#include "blackjack-client.h"
//non ancora riscritto quindi non esistente


RESULT StartMenu()
{
    struct GameMenu *menu = GameMenu_init();

    if(menu != NULL)
    {
        BeginDrawing();

        ClearBackground(DARKGREEN);

        DrawTextEx(menu->titleFont, "Blackjack", menu->vecTitlePos, 128, 5, WHITE);
        menu->playPressed = GuiButton(menu->ButtonArray[0], "PLAY");
        menu->loginPressed = GuiButton(menu->ButtonArray[1], "LOGIN");
        menu->registerPressed = GuiButton(menu->ButtonArray[2], "REGISTER");

        if (menu->onlineMode == 1)
        {
            sprintf_s(menu->moneyText, TEXT_BUFF_SIZE, "MONEY = %d", menu->moneyValue);
            DrawTextEx(menu->defaultFound, menu->moneyText, menu->vecMoneyTextPos, 64, 3, WHITE);
        }

    }

    GameMenu_free(menu);
    return -1;
}

