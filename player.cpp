#include <allegro5/allegro.h>
#include <string>
#include "player.h"
using namespace std;
Player::Player(string sprite,coordenadas posicao, int dano, int vida, int id):
Entidade(sprite,posicao, dano, vida, id){
    this->sprite = sprite;
    this->posicao = posicao;
    this->dano = dano;
    this->vida = vida;
    this->id = id;
}

void Player::mover(int x, int y){
    this->posicao.x = x;
    this->posicao.y = y;
}

void Player::ataque(){
    // ataca
}