#define BUTTON_AMOUNT 3
#define TEXT_BUFF_SIZE 65
#define WINDOW_WIDTH 625
#define WINDOW_HEIGHT 1200
#define RL_INPUT_AMOUNT 2
#define RL_BUTTON_AMOUNT 2

struct GameMenu;

struct GameMenu* GameMenu_init();
void GameMenu_free(struct GameMenu* pointer);

