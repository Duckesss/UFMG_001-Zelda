#include "Header.h"

Zone::MoveR(Game* game,Instance* instance)
{

    game->c.j++;

    int aux = 0 - (game->c.j - 1)*768;
    int i = 0 -(game->c.j - 2)*768;

    for(i = -(game->c.j - 2)*768; i>aux; i-=16){

        al_draw_bitmap(instance->map_background, i, 144 - (game->c.i - 1)*528, 0);

        if (game->player->box.xi != 0){
            game->player->box.BoxAddX(-16);
            game->player->MoveR(game);
        }

        al_draw_bitmap(instance->hud, 0, 0, 0);
        al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi, 0);
        al_flip_display();
        al_wait_for_event(game->q, &game->ev);

    }

    while (game->player->box.xi <= 0){
        game->player->MoveR(game);
        al_flip_display();
    }

    game->p.clear();

}

Zone::MoveL(Game* game, Instance* instance)
{

    game->c.j--;

    int aux = 0 - (game->c.j - 1)*768;
    int i = 0 -(game->c.j)*768;

    for(i = -(game->c.j)*768; i<aux; i+=16){

        al_draw_bitmap(instance->map_background, i, 144 - (game->c.i - 1)*528, 0);

        if (game->player->box.xf != 768){
            game->player->box.BoxAddX(16);
            game->player->MoveL(game);
        }

        al_draw_bitmap(instance->hud, 0, 0, 0);
        al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi, 0);
        al_flip_display();
        al_wait_for_event(game->q, &game->ev);

    }

    while (game->player->box.xf >= 768){
        game->player->MoveL(game);
        al_flip_display();
    }

    game->p.clear();

}

Zone::MoveU(Game* game, Instance* instance)
{

    game->c.i--;

    int aux = 144 - (game->c.i - 1)*528;
    int i = 144 - (game->c.i)*528;

    for(i = 144 - (game->c.i)*528; i<aux; i+=11){

        al_draw_bitmap(instance->map_background, -(game->c.j - 1)*768, i, 0);

        if (game->player->box.yf != 672){
            game->player->box.BoxAddY(11);
            game->player->MoveU(game);
        }

        al_draw_bitmap(instance->hud, 0, 0, 0);
        al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi, 0);
        al_flip_display();
        al_wait_for_event(game->q, &game->ev);

    }

    while(game->player->box.yf >= 672){
        game->player->MoveU(game);
    }

    game->p.clear();

}

Zone::MoveD(Game* game, Instance* instance)
{

    game->c.i++;

    int aux = 144 - (game->c.i - 1)*528;
    int i = 144 - (game->c.i-2)*528;

    for(i = 144 - (game->c.i-2)*528; i>aux; i-=11){

        al_draw_bitmap(instance->map_background, -(game->c.j - 1)*768, i, 0);

        if (game->player->box.yi != 144){
            game->player->box.BoxAddY(-11);
            game->player->MoveD(game);
        }

        al_draw_bitmap(instance->hud, 0, 0, 0);
        al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi, 0);
        al_flip_display();
        al_wait_for_event(game->q, &game->ev);

    }

    if (game->player->box.yi <= 144){
        game->player->MoveD(game);
    }

    game->p.clear();

}

Zone::Load(std::string file_path)
{

    Hitbox aux;

    std::ifstream file (file_path);

    while(!file.eof()){

        file >> aux.xi;
        file >> aux.yi;
        file >> aux.xf;
        file >> aux.yf;

        wall.push_back(aux);

        std::cout << aux.xi << ' ' << aux.yi << ' ' << aux.xf << ' ' << aux.yf << std::endl;

    }

    file.close();

}
