#include "Header.h"

Player::Load(std::string file_path)
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
        box.xf = box.xi+47;

        save_file.ignore(100, ',');
        save_file >> box.yi;
        box.yf = box.yi+47;

    save_file.ignore(100, '=');
        save_file >> c.i;

        save_file.ignore(100, ',');
        save_file >> c.j;

    save_file.ignore(100, '=');
        save_file >> progress;

    save_file.ignore(100, '=');
        save_file >> a;

    save_file.ignore(100, '=');
        save_file >> r;



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

    if (box.xf > 768 || game->zone[game->c.i-1][game->c.j-1].WallCheck(box))
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

    if (box.xf < 0 || game->zone[game->c.i-1][game->c.j-1].WallCheck(box))
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

   if (box.yi < 144 || game->zone[game->c.i-1][game->c.j-1].WallCheck(box))
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

    if (box.yf > 672 || game->zone[game->c.i-1][game->c.j-1].WallCheck(box))
        box.BoxAddY(-1);

    if (((int)box.yi)%50 <= 24)
        sprite = al_load_bitmap(".\\assets\\player_sprite_1.png");
    else
        sprite = al_load_bitmap(".\\assets\\player_sprite_0.png");

}

Player::Attack(Game* game, Instance* instance)
{

    type = INV;

    Hitbox aux = box;
    Hitbox sw;
    int i;

    //{ Animação do ataque
    sprite = att_sprite[dir*4];
    for(i=0; i<8; i++){ //Primeiro estágio de ataque
        UpdateGame(game, instance);
        al_wait_for_event(game->q, &game->ev);
    }

    sprite = att_sprite[dir*4+1];

    if (dir == 0){

        sw.xi = box.xi + 21;
        sw.xf = box.xi + 29;
        sw.yi = box.yi + 48;
        sw.yf = box.yi + 80;

        SwordCollision(game, sw);

    }
    if (dir == 1){

        sw.xi = box.xi + 48;
        sw.xf = box.xi + 80;
        sw.yi = box.yi + 24;
        sw.yf = box.yi + 32;

        SwordCollision(game, sw);
    }
    if (dir == 2){

        aux = box;
        box.yi -=36;

        sw.xi = box.xi + 15;
        sw.xf = box.xi + 23;
        sw.yi = box.yi;
        sw.yf = box.yi + 32;

        SwordCollision(game, sw);


    }
    if (dir == 3){

        aux = box;
        box.xi -=33;

        sw.xi = box.xi;
        sw.xf = box.xi + 32;
        sw.yi = box.yi + 24;
        sw.yf = box.yi + 32;

        SwordCollision(game, sw);

    }

    for(i=0; i<16; i++){
        UpdateGame(game, instance);
        al_wait_for_event(game->q, &game->ev);
    }
    box = aux;

    sprite = att_sprite[dir*4+2];
    if (dir == 2){
      aux = box;
      box.yi -=33;
    }
    if (dir == 3){
      aux = box;
      box.xi -=21;
    }
    for(i=0; i<8; i++){
        UpdateGame(game, instance);
        al_wait_for_event(game->q, &game->ev);
    }
    box = aux;

    sprite = att_sprite[dir*4+3];
    if (dir == 2){
      aux = box;
      box.yi -=9;
    }
    if (dir == 3){
      aux = box;
      box.xi -=9;
    }
    for(i=0; i<8; i++){
        UpdateGame(game, instance);
        al_wait_for_event(game->q, &game->ev);
    }
    box = aux;
    //}

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

    type = 0;

    cd = 50;

}

Player::Save(Game* game)
{

    std::ofstream file;
    if (save == 0)
        file.open(".\\entities\\save_0.txt");
    else if (save == 1)
        file.open(".\\entities\\save_1.txt");
    else if (save == 2)
        file.open(".\\entities\\save_2.txt");
    else
        return 0;

    if(game->c.i == 1 && game->c.j == 1){
        game->c.i = 2;
        box.xi = 384;
        box.yi = 366;
        box.xf = box.xi +47;
        box.yf = box.yi + 47;
    }

    file << "registered = 1" << std::endl;
    file << "name = " << name << std::endl;
    file << "health = " << health << std::endl;
    file << "hitbox = " << box.xi << ", " << box.yi << std::endl;
    file << "zone = " << game->c.i << ", " << game->c.j << std:: endl;
    file << "progress =  " << progress << std::endl;
    file << "arrow = " << a << std::endl;
    file << "rupee = " << r << std::endl;

    file.close();

}

Player::SwordCollision(Game* game, Hitbox sw)
{
    for(int i = 0; i<game->zone[game->c.i-1][game->c.j-1].e.size(); i++){
        if(sw.Collision(game->zone[game->c.i-1][game->c.j-1].e[i]->box) && game->zone[game->c.i-1][game->c.j-1].e[i]->type == TYPE_ENEMY){
            game->zone[game->c.i-1][game->c.j-1].e[i]->type = 0;
            Drop* d = new Drop(game->zone[game->c.i-1][game->c.j-1].e[i]->box);
            game->zone[game->c.i-1][game->c.j-1].e.push_back(d);
        }
        if(sw.Collision(game->zone[game->c.i-1][game->c.j-1].e[i]->box) && game->zone[game->c.i-1][game->c.j-1].e[i]->type == TYPE_BOSS){
            game->zone[game->c.i-1][game->c.j-1].e[i]->health--;
        }
    }
}


