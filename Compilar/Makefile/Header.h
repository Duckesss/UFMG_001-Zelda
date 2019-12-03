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
#include <ctime>
#include <cstdlib>
#include <math.h>
#include <sstream>

#define TYPE_ENEMY 2
#define TYPE_PROJ 3
#define TYPE_BOW 4
#define INV 5

#define TYPE_DROP_R 6
#define TYPE_DROP_H 7
#define TYPE_DROP_A 8

#define TYPE_BOSS 9

#define MAP_X 768
#define MAP_Y 528

class Game;
class Instance;
class Entity;

struct Double{
    int i;
    int j;
    float x;
    float y;
};

class Hitbox{
public:
    float xi, xf, yi, yf;

    BoxAddX(float);
    BoxAddY(float);
    bool Border();
    bool Collision(Hitbox);


};

class Entity{
public:
    Hitbox box; //Hitbox da entidade
    int health; //Vida da entidade
    int type; //Tipo auxiliar da entidade
    Double v;
    int dir;
    int cd, cd_2;
    ALLEGRO_BITMAP* sprite; //Sprite

    virtual MoveL();
    virtual MoveR();
    virtual MoveU();
    virtual MoveD();
    virtual Attack();

    virtual Update(Game*, Instance*); //Atualiza a entidade

    virtual ~Entity();
};

class Drop: public Entity{;
public:

    Drop(Hitbox);
    ~Drop();
    Update(Game*, Instance*);

};

class Projectile: public Entity{
public:

    Arrow(Game*);
    Ball(Hitbox, int);
    Update(Game*, Instance*);
    ~Projectile();

};

class Player: public Entity{
public:
    char name[9];
    int registered;
    int save, progress;
    std::vector<ALLEGRO_BITMAP*> att_sprite;
    int r, a;
    Double c;

    MoveL(Game*);
    MoveR(Game*);
    MoveU(Game*);
    MoveD(Game*);
    Attack(Game*, Instance*);
    Arrow(Game*, Instance*);
    SwordCollision(Game*, Hitbox);

    Load(std::string);
    Save(Game*);

};

class Bow: public Entity{
public:

    Update(Game*, Instance*);

    Bow();
    ~Bow();

};

class Shooter: public Entity{
public:
    Shooter(int, int);
    ~Shooter();
    Update(Game*, Instance*);

};

class Runner: public Entity{
public:
    Runner(int, int);
    ~Runner();
    Update(Game*, Instance*);

};

class Boss: public Entity{
public:
    int state;
    int hit;

    Boss();
    ~Boss();

    Update(Game*, Instance*);

};

class Zone{
public:

    std::vector<Hitbox> wall;
    std::vector<Entity*> e;

    MoveR(Game*, Instance*);
    MoveL(Game*, Instance*);
    MoveU(Game*, Instance*);
    MoveD(Game*, Instance*);

    BossZone(Game*, Instance*);

    Load(std::string file_path);
    bool WallCheck(Hitbox);

};

class Game{
public:

    bool playing;
    bool running;
    Double c;

    ALLEGRO_DISPLAY* d;
    ALLEGRO_EVENT_QUEUE* q;
    ALLEGRO_TIMER* t;
    ALLEGRO_EVENT ev;
    Player* player;
    Zone zone[3][7];


    InitCheck(); //mover para zone

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
    ALLEGRO_BITMAP* defeat_background;
    ALLEGRO_BITMAP* victory_background;
    ALLEGRO_BITMAP* hud;
    ALLEGRO_BITMAP* pause_screen;
    ALLEGRO_BITMAP* empty_heart;
    ALLEGRO_BITMAP* half_heart;
    ALLEGRO_FONT* f;
    ALLEGRO_FONT* f_1;
    ALLEGRO_FONT* f_2;



    Instance();
    virtual ~Instance();

    StartMenu(Game*);
    FileMenu(Game*);
    RegisterMenu(Game*);
    EliminationMenu(Game*);
    MainGame(Game*);
    PauseScreen(Game*);
    Victory(Game*);
    Defeat(Game*);
    Register(Game*, std::string, int);
    DisplayHealth(int, int, int);
    DisplayNum(int, int, int);

};

void UpdateGame(Game*, Instance*);

void Check(Game*, Instance*);

void out();

#endif
