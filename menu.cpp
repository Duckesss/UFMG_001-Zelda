#include <allegro5/allegro.h>
#include "menu.h"

Menu::Menu(string spritePath){
    this->sprite = spritePath;
}

void Menu::start(){
    // inicializa o jogo do começo
}

void Menu::load(){
    // inicializa o jogo a partir de um save
}

void Menu::close(){
    // fecha o jogo e desaloca toda a memória alocada durante o programa
}