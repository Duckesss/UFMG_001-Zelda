#include <allegro5/allegro.h>
#include "menu.h"

#ifndef _GAME_H
    #define _GAME_H

class Game{
    private:
        bool running;
    public:
        Game();
        void onLoop();
        void onEvent(ALLEGRO_EVENT &event);
        void onRender();
        bool isRunning();
        bool onInit();
};


#endif