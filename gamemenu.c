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
        while(!WindowShouldClose())
        {
            BeginDrawing();

            ClearBackground(DARKGREEN);

            DrawTextEx(menu->titleFont, "Blackjack", menu->vecTitlePos, 128, 5, WHITE);
            menu->playPressed = GuiButton(menu->ButtonArray[0], "PLAY");
            menu->loginPressed = GuiButton(menu->ButtonArray[1], "LOGIN");
            menu->registerPressed = GuiButton(menu->ButtonArray[2], "REGISTER");

            if (menu->isOnline == SUCCESS)
            {
                sprintf_s(menu->moneyText, TEXT_BUFF_SIZE, "MONEY = %d", menu->moneyValue);
                DrawTextEx(menu->defaultFont, menu->moneyText, menu->vecMoneyTextPos, 64, 3, WHITE);
            }

            for (int i = 0; i < BUTTON_AMOUNT; i++)
            {
                if (CheckCollisionPointRec(GetMousePosition(), menu->ButtonArray[i]))
                {
                    menu->buttonCollision = true;
                }
            }

            if (menu->buttonCollision)
            {
                SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
                menu->buttonCollision = false;
            }
            else
            {
                SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }

            EndDrawing();


            if (menu->playPressed)
            {
                RESULT return_value = menu->isOnline
                GameMenu_free(menu)
                return return_value;
            }
            else if (menu->loginPressed)
            {
                RESULT loginResult = LoginRegisterInterface(LOGIN_MODE, menu);
                menu->isOnline = loginResult;
            }
            else if (menu->registerPressed)
            {
                LoginRegisterInterface(REGISTER_MODE, menu)
            }
        }

    }

    GameMenu_free(menu);
    return -1;
}

RESULT LoginRegisterInterface(MODE mode, struct GameMenu *menu)
{
    if (mode == REGISTER_MODE)
    {
        strcpy(menu->loginMenu->buttonLabelText, "REGISTER");
    }
    else if(mode == LOGIN_MODE)
    {
        strcpy(menu->loginMenu->buttonLabelText, "LOGIN");
    }

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(DARKGREEN);

        if (GuiTextBox(menu->loginMenu->InputBoxArray[0], menu->loginMenu->usernameString, TEXT_BUFF_SIZE - 1, menu->loginMenu->usernameEditMode))
        {
            menu->loginMenu->usernameEditMode = !(menu->loginMenu->usernameEditMode);
        }

        if (GuiTextBox(menu->loginMenu->InputBoxArray[1], menu->loginMenu->passwordString, TEXT_BUFF_SIZE - 1, menu->loginMenu->passwordEditMode))
        {
            menu->loginMenu->passwordEditMode = !(menu->loginMenu->passwordEditMode);
        }

        DrawTextEx(menu->defaultFontm "USERNAME", menu->loginMenu->vecUsernameLabel, 32, 5, WHITE);
        DrawTextEx(menu->defaultFont, "PASSWORD", menu->loginMenu->vecPasswordLabel, 32, 5, WHITE);

        menu->loginMenu->loginRegisterButtonPressed = GuiButton(menu->loginMenu->ButtonArray[0], menu->loginMenu->buttonLabelText);
        menu->loginMenu->backButtonPressed = GuiButton(menu->loginMenu->ButtonArray[1], "BACK");

        for (int i = 0; i < RL_INPUT_AMOUNT; i++)
        {
            if (CheckCollisionPointRec(GetMousePosition(), menu->loginMenu->InputBoxArray[i]))
            {
                menu->loginMenu->inputCollision = true;
            }
        }

        if (!(menu->loginMenu->inputCollision))
        {
            for (int i = 0; i < RL_BUTTON_AMOUNT; i++)
            {
                if (CheckCollisionPointRec(GetMousePosition(), menu->loginMenu->ButtonArray[i]))
                {
                    menu->loginMenu->buttonCollision = true;
                }
            }
        }

        if (menu->loginMenu->inputCollision)
        {
            SetMouseCursor(MOUSE_CURSOR_IBEAM);
        }
        else if (menu->loginMenu->buttonCollision)
        {
            SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);
        }
        else
        {
            SetMouseCursor(MOUSE_CURSOR_DEFAULT);
        }

        EndDrawing();

        if (menu->loginMenu->backButtonPressed)
        {
            return CANCEL;
        }
        else if (menu->loginMenu->loginRegisterButtonPressed)
        {
            if (mode == LOGIN_MODE)
            {
                RESULT serverQueryResult = serverSend("inserire messaggio da mandare al server");
                return serverQueryResult;
            }
            else if (mode == REGISTER_MODE)
            {
                RESULT serverQueryResult = serverSend("inserire messaggio da mandare al server");
                return serverQueryResult;
            }
        }
    }
}

