#include <allegro5/allegro.h>
#include <string>
#include "entidade.h"
using namespace std;
#ifndef _PLAYER_H
    #define _PLAYER_H
class Player:public Entidade{
    public:
        Player(string sprite,coordenadas posicao, int dano, int vida, int id);
        void mover(int x, int y);
        void ataque();
};

#endif