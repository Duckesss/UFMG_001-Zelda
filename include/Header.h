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

class Game;
class Instance;
class Entity;

struct Current{
    int i;
    int j;
};

class Hitbox{

    public:
    float xi, xf, yi, yf;

    BoxAddX(int);
    BoxAddY(int);
    bool Border();
    bool Collision(Hitbox);

};

class Entity{

    public:

        Hitbox box;
        int health;
        ALLEGRO_BITMAP* sprite;
        int type;


        virtual MoveL();
        virtual MoveR();
        virtual MoveU();
        virtual MoveD();
        virtual Attack();

        virtual Effect(Game*, Instance*);

};

class Projectile: public Entity{

public:

    int vx, vy;


    Arrow(Game*);
    Update(Game*);

};

class Player: public Entity{

    public:

        int dir;
        char name[9];
        int registered;
        std::vector<ALLEGRO_BITMAP*> att_sprite;

        MoveL(Game*);
        MoveR(Game*);
        MoveU(Game*);
        MoveD(Game*);
        Attack(Game*, Instance*);
        Arrow(Game*, Instance*);

        Load(std::string, Game* game);

};

class Bow: public Entity{
    public:

        Effect(Game*, Instance*);

        Bow();

};

class Zone{

public:

    std::vector<Hitbox> wall;
    std::vector<Entity> e;

    MoveR(Game*, Instance*);
    MoveL(Game*, Instance*);
    MoveU(Game*, Instance*);
    MoveD(Game*, Instance*);

    Load(std::string file_path);

    Bow bow;

};

class Game{
    public:

        bool playing;
        Current c;

        ALLEGRO_DISPLAY* d;
        ALLEGRO_EVENT_QUEUE* q;
        ALLEGRO_TIMER* t;
        ALLEGRO_EVENT ev;
        Player* player;
        Zone zone[3][7];
        ALLEGRO_FONT* f;
        std::vector<Projectile> p;
        int scd, acd;

        InitCheck();
        bool WallCheck(Hitbox);

        LoadZones();
        Game();
        ~Game();

};

class Instance{
    public:

        ALLEGRO_BITMAP* strt_background[3];
        ALLEGRO_BITMAP* load_background;
        ALLEGRO_BITMAP* register_background;
        ALLEGRO_BITMAP* elimination_background;
        ALLEGRO_BITMAP* heart;
        ALLEGRO_BITMAP* map_background;
        ALLEGRO_BITMAP* hud;



        Instance();
        virtual ~Instance();

        StartMenu(Game*);
        FileMenu(Game*);
        RegisterMenu(Game*);
        EliminationMenu(Game*);
        MainGame(Game*);
        Register(Game*, std::string, int);

};

void UpdateGame(Game*, Instance*);

#endif
