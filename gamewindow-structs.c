#include "gamewindow-structs.h"
//#include "cardstructs.h"

struct GameWindow
{
	CARD *PlayerHand;
	CARD *DealerHand;
	DECK GameDeck;
	SIGNAL endgame_code;

	int player_card_number;
	int player_hand_score;
	int dealer_card_number;
	int dealer_hand_score;
	int money_value;
	int money_bet;
	int rel_x;
	int rel_y;

	char *money_value_string;
	char *money_bet_string;

	float screen_width;
	float screen_height;

	Font CardFont;
	Font SuitFont;
	Font DefaultFont;

	Vector2 MoneyTextVec;
	Vector2 MoneyBetTextVec;
	Vector2 suit_text_size;
	
	Rectangle *PlayerCardRecArray;
	Rectangle *DealerCardRecArray;
	Rectangle *ButtonArray;
	Rectangle ButtonAreaBGRec;

	bool hit_button_pressed;
	bool stand_button_pressed;
	bool surrend_button_pressed;
	bool doubledown_button_pressed;
	bool bet_button_pressed;
	bool end_game;
	bool retry;
	bool set_bet;
	bool updated_money;
	bool button_collision;
	bool sizes_changed;
	bool end_screen_changed;
}

struct GameWindow* GameWindow_init()
{
	struct GameWindow *gamewin = malloc(sizeof(struct GameWindow));
	if (gamewin == NULL)
		return NULL;

	gamewin->PlayerHand = malloc(sizeof(CARD * MAX_CARD_NUMBER));
	if (gamewin->PlayerHand == NULL)
		return NULL;

	gamewin->DealerHand = malloc(sizeof(CARD * MAX_CARD_NUMBER));
	if (gamewin->DealerHand == NULL)
		return NULL;

	
}
