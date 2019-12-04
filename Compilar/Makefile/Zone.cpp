#include "Header.h"

Zone::MoveR(Game* game,Instance* instance)
{ //transiçao para a direita

    game->c.j++;
    int aux = 0 - (game->c.j - 1)*MAP_X;
    int i = 0 -(game->c.j - 2)*MAP_X;

    //anima a transição
    for(i = -(game->c.j - 2)*MAP_X; i>aux; i-=16){
        al_draw_bitmap(instance->map_background, i, 144 - (game->c.i - 1)*MAP_Y, 0);
        if (game->player->box.xi != 0){
            game->player->box.BoxAddX(-16);
            game->player->MoveR(game);
        }
        al_draw_bitmap(instance->hud, 0, 0, 0);
        al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi, 0);
        al_flip_display();
        al_wait_for_event(game->q, &game->ev);
    }
    //corrige a posiçãp do jogador se houver erros
    while (game->player->box.xi <= 0){
        game->player->MoveR(game);
        al_flip_display();
    }
}

Zone::MoveL(Game* game, Instance* instance)
{ //transição para a esquerda

    game->c.j--;
    int aux = 0 - (game->c.j - 1)*MAP_X;
    int i = 0 -(game->c.j)*MAP_X;

    //se o player estiver indo para o boss
    if(game->c.j <= 0){
        BossZone(game, instance);
        return 0;
    }

    //anima a transiçao
    for(i = -(game->c.j)*MAP_X; i<aux; i+=16){
        al_draw_bitmap(instance->map_background, i, 144 - (game->c.i - 1)*MAP_Y, 0);
        if (game->player->box.xf != MAP_X){
            game->player->box.BoxAddX(16);
            game->player->MoveL(game);
        }
        al_draw_bitmap(instance->hud, 0, 0, 0);
        al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi, 0);
        al_flip_display();
        al_wait_for_event(game->q, &game->ev);
    }

    //corrige a posiçãp do jogador se houver erros
    while (game->player->box.xf >= MAP_X){
        game->player->MoveL(game);
        al_flip_display();
    }
}

Zone::MoveU(Game* game, Instance* instance)
{ //transição para cima

    game->c.i--;
    int aux = 144 - (game->c.i - 1)*MAP_Y;
    int i = 144 - (game->c.i)*MAP_Y;

    //anima a transição
    for(i = 144 - (game->c.i)*MAP_Y; i<aux; i+=11){
        al_draw_bitmap(instance->map_background, -(game->c.j - 1)*MAP_X, i, 0);
        if (game->player->box.yf != 672){
            game->player->box.BoxAddY(11);
            game->player->MoveU(game);
        }
        al_draw_bitmap(instance->hud, 0, 0, 0);
        al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi, 0);
        al_flip_display();
        al_wait_for_event(game->q, &game->ev);
    }

    //corrige a posiçãp do jogador se houver erros
    while(game->player->box.yf >= 672){
        game->player->MoveU(game);
    }
}

Zone::MoveD(Game* game, Instance* instance)
{ //trnasição para baixo

    game->c.i++;
    int aux = 144 - (game->c.i - 1)*MAP_Y;
    int i = 144 - (game->c.i-2)*MAP_Y;

    //anima a transição
    for(i = 144 - (game->c.i-2)*MAP_Y; i>aux; i-=11){
        al_draw_bitmap(instance->map_background, -(game->c.j - 1)*MAP_X, i, 0);
        if (game->player->box.yi != 144){
            game->player->box.BoxAddY(-11);
            game->player->MoveD(game);
        }
        al_draw_bitmap(instance->hud, 0, 0, 0);
        al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi, 0);
        al_flip_display();
        al_wait_for_event(game->q, &game->ev);
    }

    //corrige a posiçãp do jogador se houver erros
    while (game->player->box.yi <= 144){
        game->player->MoveD(game);
    }
}

Zone::BossZone(Game* game, Instance* instance)
{ //faz a animação para a sala do boss

    int i = 0;
    game->c.i = 1;
    game->c.j = 1;
    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    while(i < 50){ //delay
        al_wait_for_event(game->q, &game->ev);
        i++;
    }
    game->player->box.xi = 576;
    game->player->box.xf = 623;
    game->player->box.yi = 384;
    game->player->box.yf = 431;
}

Zone::Load(string file_path)
{ //carrega as paredes

    //le o arquivo e registra até acabar o .txt
    Hitbox aux;
    ifstream file (file_path);
    while(!file.eof()){
        file >> aux.xi;
        file >> aux.yi;
        file >> aux.xf;
        file >> aux.yf;
        wall.push_back(aux);
    }
    file.close();
}

bool Zone::WallCheck(Hitbox box)
{ //verifica se a hitbox entrou em colisão com alguma parede
    for(int i = 0; i<wall.size(); i++){
        if(box.Collision(wall[i]))
            return true;
    }
    return false;
}


