#include <allegro5/allegro.h>
#include <string>
#include "entidade.h"
using namespace std;


Entidade::Entidade(string sprite,coordenadas posicao, int dano, int vida, int id){
    this->sprite = sprite;
    this->posicao = posicao;
    this->dano = dano;
    this->vida = vida;
    this->id = id;
}

