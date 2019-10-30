#include <allegro5/allegro.h>
#include <iostream>
#include "game.h"
using namespace std;

Game::Game(){
    running = true;
}

bool Game::onInit(){
    if(!al_init()) {
      cout << "failed to initialize allegro!" << endl;
      return false;
   }
   return true;
}

void Game::onEvent(ALLEGRO_EVENT &evento){
    // cuida dos eventos
}

void Game::onLoop(){
    // atualiza as informações a cada loop
}

void Game::onRender(){
    // cuida de renderizar as informações
}

bool Game::isRunning(){  // checa se o jogo está rodando
    return this->running;
}