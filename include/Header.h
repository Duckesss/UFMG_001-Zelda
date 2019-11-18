#ifndef HEADER_H
#define HEADER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>
#include <vector>
#include <cstdio>
#include <fstream>
#include <string>
#include <conio.h>
#include <stdio.h>


typedef struct Hitbox{

    int xi, xf, yi, yf;

}Hitbox;

class Entity{

    public:

        Hitbox hitbox;
        int health;
        std::vector<ALLEGRO_BITMAP*> sprite;

};

class Player: public Entity{

    public:

        int i, j;
        char name[8];
        int registered;

        Load(std::string);

};

class Game{
    public:

        bool playing;

        ALLEGRO_DISPLAY* d;
        ALLEGRO_EVENT_QUEUE* q;
        ALLEGRO_TIMER* t;
        ALLEGRO_EVENT ev;
        Player player;
        ALLEGRO_FONT* f;

        InitCheck();

        Game();
        ~Game();

};

class Instance{
    private:
        ALLEGRO_BITMAP* dark_background;
        ALLEGRO_BITMAP* zelda_sprites[8];
        quitGame(Game* game,int hasEventQueue);
        att_heartX(int &heartX,int posicao,Player save[], int decrease);
        dicionario_heartX(int &heartX, int coordenadas);
       gameLoop(Game* game);
    public:

        ALLEGRO_BITMAP* strt_background[3];
        ALLEGRO_BITMAP* load_background;
        ALLEGRO_BITMAP* register_background;
        ALLEGRO_BITMAP* elimination_background;
        ALLEGRO_BITMAP* heart;


        Instance();
        virtual ~Instance();

        StartMenu(Game*);
        FileMenu(Game*);
        RegisterMenu(Game*);
        EliminationMenu(Game*);
        MainGame(Game*);
        Register(Game*, std::string, int);

};



#endif
