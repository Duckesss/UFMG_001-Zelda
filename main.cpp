#include <allegro5/allegro.h>
#include "game.h"

int main(int argc, char **argv) {
    Game game = Game();
    game.onInit();
    return 0;
}
