#include "Header.h"

void Check(Game* game, Instance* Instance){ //garante que algumas variáveis não vão ultrapassar seu limite

    //garante que não vai tentar acessar um valor que não está na matriz
    if(game->c.i > 3)
        game->c.i = 3;
    if(game->c.i < 1)
        game->c.i = 1;
    if(game->c.j > 7)
        game->c.j = 7;
    if(game->c.j < 1)
        game->c.j = 1;

    //evita valores que são maiores que a HUD suporta
    if(game->player->health > 16)
        game->player->health = 16;
    if(game->player->a > 999)
        game->player->a = 999;
    if(game->player->r > 999)
        game->player->r = 999;
    if(game->player->a < 0)
        game->player->a = 0;
    if(game->player->r < 0)
        game->player->r = 0;


}

void UpdateGame(Game* game, Instance* instance){ //atualiza o jogo

    //{atualiza os cooldowns do jogador
    game->player->cd--;
    game->player->cd_2--;
    if(game->player->cd<0)
        game->player->cd = 0;
    if(game->player->cd_2<0)
        game->player->cd_2 = 0;
    //}

    //desenha a tela
    al_draw_bitmap(instance->map_background, 0 - (game->c.j - 1)*MAP_X, 144 - (game->c.i - 1)*MAP_Y, 0);
    al_draw_bitmap(instance->hud, 0, 0, 0);
    al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi, 0);

    //atualiza as entidades e as desenha se forem validas
    for(int i=0; i<game->zone[game->c.i-1][game->c.j-1].e.size(); i++){ //percorrendo o vetor de entidades da zona atual

        if(game->zone[game->c.i-1][game->c.j-1].e[i]->type !=0) // se a entidade ainda for valida, atualiza ela
            game->zone[game->c.i-1][game->c.j-1].e[i]->Update(game, instance);

        if(game->zone[game->c.i-1][game->c.j-1].e[i]->type !=0 && game->zone[game->c.i-1][game->c.j-1].e[i]->type != TYPE_BOW)// se a entidade ainda for valida, desenha ela
            al_draw_bitmap(game->zone[game->c.i-1][game->c.j-1].e[i]->sprite, game->zone[game->c.i-1][game->c.j-1].e[i]->box.xi, game->zone[game->c.i-1][game->c.j-1].e[i]->box.yi, 0);

    }

    //atualiza informações do jogo
    instance->DisplayHealth(game->player->health, 435, 72);
    instance->DisplayNum(game->player->r, 195, 24);
    if(game->player->progress == 1)
        instance->DisplayNum(game->player->a, 195, 72);
    al_flip_display();

    //checa consistencia dos dados
    Check(game, instance);

}

int main(){ //main

    srand(time(0)); //da set em uma nova seed para ser aleatorio

    Game game = Game(); //cria o jogo
    Instance instance = Instance(); //cria uma classe instance

    instance.StartMenu(&game); //Start o menu principal

    //finaliza o jogo e livra as memorias
    delete &instance;
    delete &game;

    return 1;

}
