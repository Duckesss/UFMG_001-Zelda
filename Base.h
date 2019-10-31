#ifndef BASE_H
#define BASE_H

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

typedef struct Point{

    int x;
    int y;

}Point;

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

        Instance();
        virtual ~Instance();

        StartMenu(Game*);
        FileMenu(Game*);
        RegisterMenu(Game*);

};

class Entity{

    public:

        Point pos;
        int hp;
        std::vector<ALLEGRO_BITMAP*> sprite;

        virtual MoveU();
        virtual MoveD();
        virtual MoveR();
        virtual MoveL();
        virtual Attack();
        virtual Damage();

};

class Player: public Entity{

    public:

        MoveU();
        MoveD();
        MoveR();
        MoveL();
        Attack();
        Damage();


};

#endif // BASE_H
