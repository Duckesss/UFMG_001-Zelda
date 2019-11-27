#include "Header.h"

Player::Load(std::string file_path, Game* game)
{

//{
    std::ifstream save_file;
    save_file.open(file_path);

    save_file.ignore(100, '=');
        save_file >> registered;

    save_file.ignore(100, '=');
        save_file >> name;

    save_file.ignore(100, '=');
        save_file >> health;

    save_file.ignore(100, '=');
        save_file >> box.xi;
        box.xf = box.xi + 48;

        save_file.ignore(100, ',');
        save_file >> box.yi;
        box.yf = box.yi+48;

    save_file.ignore(100, '=');
        save_file >> game->c.i;

        save_file.ignore(100, ',');
        save_file >> game->c.j;

    save_file.close();

//}

sprite = al_load_bitmap(".\\assets\\player_sprite_0.png");

att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_0.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_1.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_2.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_3.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_4.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_5.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_6.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_7.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_8.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_9.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_10.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_11.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_12.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_13.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_14.png"));
att_sprite.push_back(al_load_bitmap(".\\assets\\att_sprite_15.png"));



}

Player::MoveR(Game* game)
{
    box.BoxAddX(1);
    dir = 1;

    if (box.xf > 768 || game->WallCheck(box))
        box.BoxAddX(-1);

    if (((int)box.xi)%50 <= 24)
        sprite = al_load_bitmap(".\\assets\\player_sprite_3.png");
    else
        sprite = al_load_bitmap(".\\assets\\player_sprite_2.png");

}

Player::MoveL(Game* game)
{

    box.BoxAddX(-1);
    dir = 3;

    if (box.xf < 0 || game->WallCheck(box))
        box.BoxAddX(1);

    if (((int)box.xi)%50 <= 24)
        sprite = al_load_bitmap(".\\assets\\player_sprite_7.png");
    else
        sprite = al_load_bitmap(".\\assets\\player_sprite_6.png");

}

Player::MoveU(Game* game)
{

    box.BoxAddY(-1);
    dir = 2;

   if (box.yi < 144 || game->WallCheck(box))
        box.BoxAddY(1);

    if (((int)box.yi)%50 <= 24)
        this->sprite = al_load_bitmap(".\\assets\\player_sprite_5.png");
    else
        this->sprite = al_load_bitmap(".\\assets\\player_sprite_4.png");

}

Player::MoveD(Game* game)
{

    box.BoxAddY(1);
    dir = 0;

    if (box.yf > 672 || game->WallCheck(box))
        box.BoxAddY(-1);

    if (((int)box.yi)%50 <= 24)
        sprite = al_load_bitmap(".\\assets\\player_sprite_1.png");
    else
        sprite = al_load_bitmap(".\\assets\\player_sprite_0.png");

}

Player::Attack(Game* game, Instance* instance)
{

    Hitbox aux = box;
    int i;

    sprite = att_sprite[dir*4];
    for(i=0; i<8; i++){
        UpdateGame(game, instance);
        al_wait_for_event(game->q, &game->ev);
    }

    sprite = att_sprite[dir*4+1];
    if (dir == 0){

      //dar dano nos inimigos

    }
    if (dir == 1){

      //dar dano nos inimigos

    }
    if (dir == 2){

      aux = box;
      box.yi -=36;

      //dar dano nos inimigos

    }
    if (dir == 3){

      aux = box;
      box.xi -=33;

      //dar dano nos inimigos

    }
    for(i=0; i<16; i++){
        UpdateGame(game, instance);
        al_wait_for_event(game->q, &game->ev);
    }
    box = aux;

    sprite = att_sprite[dir*4+2];
    if (dir == 0){

      //dar dano nos inimigos

    }
    if (dir == 1){

      //dar dano nos inimigos

    }
    if (dir == 2){

      aux = box;
      box.yi -=33;

      //dar dano nos inimigos

    }
    if (dir == 3){

      aux = box;
      box.xi -=21;

      //dar dano nos inimigos

    }
    for(i=0; i<8; i++){
        UpdateGame(game, instance);
        al_wait_for_event(game->q, &game->ev);
    }
    box = aux;

    sprite = att_sprite[dir*4+3];
    if (dir == 0){

      //dar dano nos inimigos

    }
    if (dir == 1){

      //dar dano nos inimigos

    }
    if (dir == 2){

      aux = box;
      box.yi -=9;

      //dar dano nos inimigos

    }
    if (dir == 3){

      aux = box;
      box.xi -=9;

      //dar dano nos inimigos

    }
    for(i=0; i<8; i++){
        UpdateGame(game, instance);
        al_wait_for_event(game->q, &game->ev);
    }
    box = aux;



//{
    if(dir == 1)
        sprite = sprite = al_load_bitmap(".\\assets\\player_sprite_2.png");
    if(dir == 3)
        sprite = sprite = al_load_bitmap(".\\assets\\player_sprite_6.png");
    if(dir == 2)
        sprite = sprite = al_load_bitmap(".\\assets\\player_sprite_4.png");
    if(dir == 0)
        sprite = sprite = al_load_bitmap(".\\assets\\player_sprite_0.png");

    UpdateGame(game, instance);
    al_wait_for_event(game->q, &game->ev);

//}

    game->scd = 50;

}
