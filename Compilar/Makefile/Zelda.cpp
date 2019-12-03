#include "Header.h"

void out(){

    std::cout << 'a' << std::endl;

}

void Check(Game* game, Instance* Instance){

    if(game->c.i > 3)
        game->c.i = 3;
    if(game->c.i < 1)
        game->c.i = 1;
    if(game->c.j > 7)
        game->c.j = 7;
    if(game->c.j < 1)
        game->c.j = 1;

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

void UpdateGame(Game* game, Instance* instance){ //Atualiza jogo

    //{ Atualiza cooldowns
    game->player->cd--;
    game->player->cd_2--;
    if(game->player->cd<0)
        game->player->cd = 0;
    if(game->player->cd_2<0)
        game->player->cd_2 = 0;
    //}

    al_draw_bitmap(instance->map_background, 0 - (game->c.j - 1)*MAP_X, 144 - (game->c.i - 1)*MAP_Y, 0);
    al_draw_bitmap(instance->hud, 0, 0, 0);
    al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi, 0);

    //{ Atualiza entidades
    for(int i=0; i<game->zone[game->c.i-1][game->c.j-1].e.size(); i++){

        if(game->zone[game->c.i-1][game->c.j-1].e[i]->type !=0)
            game->zone[game->c.i-1][game->c.j-1].e[i]->Update(game, instance);

        if(game->zone[game->c.i-1][game->c.j-1].e[i]->type !=0 && game->zone[game->c.i-1][game->c.j-1].e[i]->type != TYPE_BOW)
            al_draw_bitmap(game->zone[game->c.i-1][game->c.j-1].e[i]->sprite, game->zone[game->c.i-1][game->c.j-1].e[i]->box.xi, game->zone[game->c.i-1][game->c.j-1].e[i]->box.yi, 0);

    }
    //}

    instance->DisplayHealth(game->player->health, 435, 72);
    instance->DisplayNum(game->player->r, 195, 24);
    if(game->player->progress == 1)
        instance->DisplayNum(game->player->a, 195, 72);

    Check(game, instance);
    al_flip_display();

}

int main(){

    srand(time(0));

    Game game = Game();
    Instance instance = Instance();

    instance.StartMenu(&game);

    delete &instance;
    delete &game;

    return 1;

}
