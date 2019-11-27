#include "Header.h"

void UpdateGame(Game* game, Instance* instance){

    int i;

    game->scd--;
    game->acd--;
    if(game->acd<0)
        game->acd = 0;
    if(game->scd<0)
        game->scd = 0;

    al_draw_bitmap(instance->map_background, 0 - (game->c.j - 1)*768, 144 - (game->c.i - 1)*528, 0);
    al_draw_bitmap(instance->hud, 0, 0, 0);
    al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi, 0);

    for(i=0; i<game->p.size(); i++){

        game->p[i].Update(game);

        if(game->p[i].type !=0 )
            al_draw_bitmap(game->p[i].sprite, game->p[i].box.xi, game->p[i].box.yi, 0);

    }

    al_flip_display();

}

int main(){

    Game game = Game();
    Instance instance = Instance();

    instance.StartMenu(&game);

    delete &instance;
    delete &game;

    return 1;

}
