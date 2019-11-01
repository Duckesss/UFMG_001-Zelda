#include <allegro5/allegro.h>
#include <string>
using namespace std;

#ifndef _ENTIDADE_H
    #define _ENTIDADE_H

struct coordenadas{
    int x;
    int y;
};

class Entidade{
    protected:
        string sprite;
        coordenadas posicao;
        int dano;
        int vida;
        int id;
    public:
        Entidade(string sprite,coordenadas posicao, int dano, int vida, int id);
        virtual void mover() = 0;
        virtual void ataque() = 0;
};

#endif
