#include <stdlib.h>
#include <raylib.h>
#include <raygui.h>
#include <string.h>
#include <stdbool.h>

#include "gamemenu-structs.h"
//temporaneo per via della necessità della struct all'interno

#define BUTTON_AMOUNT 3
#define TEXT_BUFF_SIZE 65
#define WINDOW_WIDTH 625
#define WINDOW_HEIGHT 1200
#define RL_INPUT_AMOUNT 2
#define RL_BUTTON_AMOUNT 2

struct GameMenu
{
    Vector2 vecTitlePos;
    Vector2 vecMoneyTextPos;
    Rectangle *ButtonArray;

    bool playPressed;
    bool loginPressed;
    bool registerPressed;
    bool buttonCollision;

    int onlineMode;
    int moneyValue;

    char *moneyText;

    Font titleFont;
    Font defaultFont;

    struct LoginRegisterMenu
    {
        bool usernameEditMode;
        bool passwordEditMode;
        bool loginRegisterButtonPressed;
        bool backButtonPressed;
        bool buttonCollision;
        bool inputCollision;

        Rectangle *InputBoxArray;
        Rectangle *ButtonArray;
        Vector2 vecUsernameLabel;
        Vector2 vecPasswordLabel;

        char *buttonLabelText;
        char *usernameString;
        char *passwordString;
    }, loginMenu;

};


struct GameMenu* GameMenu_init()
{
    
    struct GameMenu *menu = malloc(sizeof(struct GameMenu));
    if (menu == NULL)
        return NULL;

    menu->moneyText = malloc(TEXT_BUFF_SIZE * sizeof(char));
    if (menu->moneyText == NULL)
        return NULL;

    menu->ButtonArray = malloc(BUTTON_AMOUNT * sizeof(Rectangle));
    if (menu->ButtonArray == NULL)
        return NULL;


    menu->playPressed = false;
    menu->loginPressed = false;
    menu->registerPressed = false;
    menu->cursorCollisionWithButtons = false;
    menu->onlineMode = 0;
    menu->moneyValue = 0;
    menu->moneyText = "";
    menu->titleFont = LoadFontEx("JqkasWild-w1YD6.ttf", 128, 0, 250);
    menu->defaultFont = GetFontDefault();

    menu->vecTitlePos.x = WINDOW_WIDTH * 0.03f;
    menu->vecTitlePos.y = WINDOW_HEIGHT * 0.03f;
    menu->vecMoneyTextPos.x = WINDOW_WIDTH * 0.4f;
    menu->vecMoneyTextPos.y = WINDOW_HEIGHT * 0.5f;

    for (int i = 0; i < BUTTON_AMOUNT; i++)
    {
        menu->ButtonArray[i].x = WINDOW_WIDTH * 0.05f;
        menu->ButtonArray[i].y = (0.3f + (i * 0.15f)) * WINDOW_HEIGHT;
        menu->ButtonArray[i].width = WINDOW_WIDTH * 0.3f;
        menu->ButtonArray[i].height = WINDOW_HEIGHT * 0.1f;
    }


    menu->loginMenu->InputBoxArray = malloc(RL_INPUT_AMOUNT * sizeof(Rectangle));
    if (menu->loginMenu->InputBoxArray == NULL)
        return NULL;

    menu->loginMenu->ButtonArray = malloc(RL_BUTTON_AMOUNT * sizeof(Rectangle));
    if (menu->loginMenu->ButtonArray == NULL)
        return NULL;

    menu->loginMenu->buttonLabelText = malloc(10 * sizeof(char));
    if (menu->loginMenu->buttonLabelText == NULL)
        return NULL;

    menu->loginMenu->usernameString = malloc(TEXT_BUFF_SIZE * sizeof(char));
    if (menu->loginMenu->usernameString == NULL)
        return NULL;

    menu->loginMenu->passwordString = malloc(TEXT_BUFF_SIZE * sizeof(char));
    if (menu->loginMenu->passwordString == NULL)
        return NULL;


    menu->loginMenu->usernameEditMode = false;
    menu->loginMenu->passwordEditMode = false;
    menu->loginMenu->loginRegisterButtonPressed = false;
    menu->loginMenu->backButtonPressed = false;
    menu->loginMenu->buttonCollision = false;
    menu->loginMenu->inputCollision = false;

    menu->loginMenu->buttonLabelText = "";
    menu->loginMenu->usernameString = "";
    menu->loginMenu->passwordstring = "";

    menu->loginMenu->vecUsernameLabel.x = WINDOW_WIDTH * 0.1f;
    menu->loginMenu->vecUsernameLabel.y = WINDOW_HEIGHT * 0.15f;
    menu->loginMenu->vecPasswordLabel.x = WINDOW_WIDTH * 0.1f;
    menu->loginMenu->vecPasswordLabel.y = WINDOW_HEIGHT * 0.4f;

    for (int i = 0; i < RL_INPUT_AMOUNT; i++)
    {
        menu->loginMenu->InputBoxArray[i].x = WINDOW_WIDTH * 0.1f;
        menu->loginMenu->InputBoxArray[i].y = (0.2f + (0.25f * i)) * WINDOW_HEIGHT;
        menu->loginMenu->InputBoxArray[i].width = WINDOW_WIDTH  * 0.5f;
        menu->loginMenu->InputBoxArray[i].height = WINDOW_HEIGHT * 0.15f;
    }

    for (int i = 0; i < RL_BUTTON_AMOUNT; i++)
    {
        menu->loginMenu->ButtonArray[i].x = (0.12f + (0.23f * i)) * WINDOW_HEIGHT;
        menu->loginMenu->ButtonArray[i].y = WINDOW_HEIGHT * 0.75f;
        menu->loginMenu->ButtonArray[i].width = WINDOW_WIDTH * 0.2f;
        menu->loginMenu->ButtonArray[i].height = WINDOW_HEIGHT * 0.1f;
    }

    if (mode == REGISTER_MODE)
    {
        strcpy(buttonLabelText, "REGISTER");
    }
    else if(mode == LOGIN_MODE)
    {
        strcpy(buttonLabelText, "LOGIN");
    }

    return menu;
}

void GameMenu_free(struct GameMenu* pointer)
{
    free(pointer->moneyText);
    free(pointer->ButtonArray);
    free(pointer->loginMenu->InputBoxArray);
    free(pointer->loginMenu->ButtonArray);
    free(pointer->loginMenu->buttonLabelText);
    free(pointer->loginMenu->usernameString);
    free(pointer->loginMenu->passwordString);
    free(pointer);
}