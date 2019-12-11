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

using namespace std;

class Game;
class Instance;
class Entity;

struct Double{ //struct para carregar alguns valores específicos
    int i; //posição i da matriz
    int j; //posição j da matriz
    float x; //parte x de um vetor velocidade
    float y; //parte y de um vetor velocidade
};

class Hitbox{ //hitbox de algo
public:
    float xi, xf, yi, yf; //pontos iniciais e finais, que geram a "caixa"

    BoxAddX(float); //move a caixa para a direita ou esquerda
    BoxAddY(float); //move a caixa para cima ou baixo
    bool Border(); //checa se a caixa esta no limite do mapa
    bool Collision(Hitbox); //compara se duas caixas colidiram
};

class Entity{ //classe pai das entidades
public:
    Hitbox box; //hitbox da entidade
    int health; //vida da entidade
    int type; //tipo da entidade
    Double v; //vetor velocidade
    int dir; //direção da unidade
    int cd, cd_2; //cooldowns das entidades
    ALLEGRO_BITMAP* sprite; //sprites

    virtual Update(Game*, Instance*); //atualiza a entidade

    virtual ~Entity(); //destrutor da classe
};

class Drop: public Entity{ //drops de inimigos
public:
    Update(Game*, Instance*);

    Drop(Hitbox); //construtor da classe
    ~Drop();
};

class Projectile: public Entity{ //projéteis do jogo
public:
    Update(Game*, Instance*);

    Arrow(Game*); //faz o projétil ser uma flecha
    Ball(Hitbox, int); //cria um projetil bola com um sprite decidido pelo int
    ~Projectile();
};

class Player: public Entity{ //classe do jogador
public:
    char name[9]; //nome do jogaor
    int registered; //se o save aberto está registrado
    int save; //qual save esse jogador pertence
    int progress; //o progresso do jogador
    vector<ALLEGRO_BITMAP*> att_sprite; //vetor com os sprites de ataque
    int r, a; //contagem de rupees e flechas respectivamente

    //movimenta o jogador
    MoveL(Game*);
    MoveR(Game*);
    MoveU(Game*);
    MoveD(Game*);

    Attack(Game*, Instance*); //ataque do jogadorr
    SwordCollision(Game*, Hitbox); //verifica e realiza o contato da espada com inimigo

    Load(string); //carrega os dados do jogador
    Save(Game*); //salva o progresso do jogador no txt dele
};

class Bow: public Entity{ //arco
public:
    Update(Game*, Instance*);

    Bow(); //cria o arco
    ~Bow();
};

class Shooter: public Entity{ //inimigo que atira
public:
    Update(Game*, Instance*);

    Shooter(int, int); //cria um atirador na posição indicada
    ~Shooter();
};

class Runner: public Entity{ //inimigo que segue
public:
    Update(Game*, Instance*);

    Runner(int, int); //cria um corredor na posição indicada
    ~Runner();
};

class Boss: public Entity{ //chefão final do jogo
public:
    int state; //estado de ataque do boss
    int hit; //verifica se o jogador já foi acertado pelo ataque

    Update(Game*, Instance*);

    Boss(); //cria o boss na posição dele
    ~Boss();
};

class Zone{ //zonas do jogo
public:
    vector<Hitbox> wall; //vetor de hitbox das paredes da zona
    vector<Entity*> e; //vetor das entidades na zona

    //realiza a animação de transição da zona
    MoveR(Game*, Instance*);
    MoveL(Game*, Instance*);
    MoveU(Game*, Instance*);
    MoveD(Game*, Instance*);
    BossZone(Game*, Instance*);

    Load(string file_path); //carrega as paredes da zona
    bool WallCheck(Hitbox); //verifica se houve alguma colisão nas paredes da zona
};

class Game{ //os dados principais do jogo
public:
    ALLEGRO_DISPLAY* d; //display
    ALLEGRO_EVENT_QUEUE* q; //fila de eventos
    ALLEGRO_TIMER* t; //timer
    ALLEGRO_EVENT ev; //evento de allegro
    Player* player; //jogador principal
    Zone zone[3][7]; //zonas do jogo
    bool playing; //bool se o jogo esta sendo jogado
    bool running; //bool se o programa deve ser mantido aberto
    Double c; //a posição atual na matriz

    InitCheck(); //checa se tudo inicializou corretamente
    LoadZones(); //prepara todas as zonas

    Game(); //inicia o jogo e Allegro
    ~Game(); //fecha o jogo e se livra da memória
};

class Instance{
public:
    ALLEGRO_BITMAP* strt_background[3]; //imagens para fazer a an
    ALLEGRO_BITMAP* load_background; //bakcground da tela de load
    ALLEGRO_BITMAP* register_background; //background da tela de registro
    ALLEGRO_BITMAP* elimination_background; //background da tela de eliminacao
    ALLEGRO_BITMAP* defeat_background; //background da tela de derrota
    ALLEGRO_BITMAP* victory_background; //background da tela de vitoria
    ALLEGRO_BITMAP* map_background; //mapa do jogo
    ALLEGRO_BITMAP* hud; //hud
    ALLEGRO_BITMAP* pause_screen; //tela de pause
    ALLEGRO_BITMAP* heart; //sprite do coracao cheio
    ALLEGRO_BITMAP* empty_heart; //sprite coracao vazio
    ALLEGRO_BITMAP* half_heart; //sprite meio coracao
    ALLEGRO_FONT* f; //fonte 24
    ALLEGRO_FONT* f_1; //fonte 48
    ALLEGRO_FONT* f_2; //fonte 72

    StartMenu(Game*); //menu inicial
    FileMenu(Game*); //mostra os saves
    RegisterMenu(Game*); //permite registrar novos saves
    EliminationMenu(Game*); //permite "deletar" saves
    MainGame(Game*); //inicial o jogo principal
    PauseScreen(Game*); //salva pausa o jogo
    Victory(Game*); //tela de vitoria
    Defeat(Game*); //tela de derrota
    Register(Game*, string, int); //registrar um save
    DisplayHealth(int, int, int); //mostrar vida
    DisplayNum(int, int, int); //mostrar um numero

    Instance(); //cria instancia
    ~Instance(); //libera instancia

};

void UpdateGame(Game*, Instance*); //atualiza todo o jogo

void Check(Game*, Instance*); //checa se há lixo e corrige

#endif
