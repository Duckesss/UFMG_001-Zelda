#include "Header.h"

int main(){

    Game game = Game();
    Instance instance = Instance();

    instance.StartMenu(&game);

    delete &instance;
    delete &game;

    return 0;

}
