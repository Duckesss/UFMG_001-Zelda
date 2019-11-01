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

typedef struct Hitbox{

    int xi, xf, yi, yf;

}Hitbox;

class Game
{
    public:

        bool playing;

        ALLEGRO_DISPLAY* d;
        ALLEGRO_EVENT_QUEUE* q;
        ALLEGRO_TIMER* t;
        ALLEGRO_EVENT ev;

        InitCheck();

        Game();
        ~Game();

};

class Instance
{
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

};

class Entity{

    public:

        Hitbox hitbox;
        int hp;
        std::vector<ALLEGRO_BITMAP*> sprite;

        virtual MoveU();
        virtual MoveD();
        virtual MoveR();
        virtual MoveL();
        virtual Attack();
        virtual Damage();

        Load(std::string);
        ~Entity();

};

class Player: public Entity{

    public:

        int save;

        Load(std::string);
        MoveU();
        MoveD();
        MoveR();
        MoveL();
        Attack();
        Damage();


};

#endif
