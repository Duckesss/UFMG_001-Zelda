#include "Header.h"

Entity::MoveL(){}

Entity::MoveU(){}

Entity::MoveD(){}

Entity::MoveR(){}

Entity::Attack(){}

Entity::Effect(Game*, Instance*){}

Projectile::Update(Game* game)
{

    box.BoxAddX(vx);
    box.BoxAddY(vy);

    if(box.Border() || game->WallCheck(box)){
        type = 0;
    }
}

Projectile::Arrow(Game* game)
{

    type = 1;

    if(game->player->dir == 0){
        sprite = al_load_bitmap(".\\assets\\arrow_0.png");
        box.xi = game->player->box.xi + 18;
        box.xf = box.xi + 15;
        box.yi = game->player->box.yf + 1;
        box.yf = box.yi + 48;
        vx = 0;
        vy = 2;
    }

    else if(game->player->dir == 1){
        sprite = al_load_bitmap(".\\assets\\arrow_1.png");
        box.xi = game->player->box.xf + 1;
        box.xf = box.xi + 48;
        box.yi = game->player->box.yi + 21;
        box.yf = box.yi + 15;
        vx = 2;
        vy = 0;
    }

    else if(game->player->dir == 2){
        sprite = al_load_bitmap(".\\assets\\arrow_2.png");
        box.xi = game->player->box.xi + 12;
        box.xf = box.xi + 15;
        box.yi = game->player->box.yi - 49;
        box.yf = box.yi + 48;
        vx = 0;
        vy = -2;
    }

    else if(game->player->dir == 3){
        sprite = al_load_bitmap(".\\assets\\arrow_3.png");
        box.xi = game->player->box.xi - 49;
        box.xf = box.xi + 48;
        box.yi = game->player->box.yi + 21;
        box.yf = box.yi + 15;
        vx = -2;
        vy = 0;
    }

    game->player->sprite = game->player->att_sprite[game->player->dir*4];

    game->acd = 100;
}

Bow::Bow()
{

    type = 1;

    box.xi = 384;
    box.yi = 339;
    box.xf = box.xi + 48;
    box.yf = box.yf + 48;


}

Bow::Effect(Game* game, Instance* instance)
{

    type = 0;

    instance->map_background = al_load_bitmap(".\\assets\\map_background_1.png");
    instance->hud = al_load_bitmap(".\\assets\\hud_1.png");
    game->player->sprite = al_load_bitmap(".\\assets\\bow_sprite.png");

    al_draw_bitmap(instance->map_background, 0 - (game->c.j - 1)*768, 144 - (game->c.i - 1)*528, 0);
    al_draw_bitmap(instance->hud, 0, 0, 0);
    al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi-48, 0);

    al_flip_display();

    al_rest(1.0/1);

    game->player->sprite = al_load_bitmap(".\\assets\\player_sprite_0.png");

}
