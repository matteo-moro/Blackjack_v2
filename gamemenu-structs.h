typedef enum login_mode
{
    LOGIN_MODE = 0,
    REGISTER_MODE
} MODE;
//questo enum deve essere spostato da un altra parte visto che viene usato in giro, incluso in main
//idealmente dovrei creare un file generale per le struct usate da più parti e usare ifndef per evitare conflitti
//non è un qualcosa che voglio fare oggi
//ricreare onlinemode struct in futuro

//typedef non è usato perchè voglio modificare elementi di membri dello struct direttamente
//allo stesso tempo voglio tenere l'header pulito
struct GameMenu;

struct GameMenu* GameMenu_init();
void GameMenu_free(struct GameMenu* pointer);

