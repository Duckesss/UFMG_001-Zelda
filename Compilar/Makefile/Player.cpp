#include "Header.h"

Player::Load(string file_path)
{ //cria o jogador

//{ carregaga dados do save
    ifstream save_file;
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
        save_file >> v.i;

        save_file.ignore(100, ',');
        save_file >> v.j;

    save_file.ignore(100, '=');
        save_file >> progress;

    save_file.ignore(100, '=');
        save_file >> a;

    save_file.ignore(100, '=');
        save_file >> r;



    save_file.close();
//}

    //carrega os sprites do jogador
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
{ //move o jogador para direita

    //muda a posição e direção
    box.BoxAddX(1);
    dir = 1;

    //desfaz o movimento se o jogador colidir
    if (box.xf > 768 || game->zone[game->c.i-1][game->c.j-1].WallCheck(box))
        box.BoxAddX(-1);

    if (((int)box.xi)%50 <= 24)
        sprite = al_load_bitmap(".\\assets\\player_sprite_3.png");
    else sprite = al_load_bitmap(".\\assets\\player_sprite_2.png");
}

Player::MoveL(Game* game)
{ //move o jogador para a esquerda

    //muda a posição e direção
    box.BoxAddX(-1);
    dir = 3;

    //desfaz o movimento se o jogador colidir
    if (box.xf < 0 || game->zone[game->c.i-1][game->c.j-1].WallCheck(box))
        box.BoxAddX(1);

    //animação de movimento
    if (((int)box.xi)%50 <= 24)
        sprite = al_load_bitmap(".\\assets\\player_sprite_7.png");
    else sprite = al_load_bitmap(".\\assets\\player_sprite_6.png");
}

Player::MoveU(Game* game)
{ //move o jogador para cima

    //muda posição e direção
    box.BoxAddY(-1);
    dir = 2;

    //desfaz o movimento se o jogador colidir
    if (box.yi < 144 || game->zone[game->c.i-1][game->c.j-1].WallCheck(box))
        box.BoxAddY(1);

    //anima o movimento
    if (((int)box.yi)%50 <= 24)
        sprite = al_load_bitmap(".\\assets\\player_sprite_5.png");
    else sprite = al_load_bitmap(".\\assets\\player_sprite_4.png");
}

Player::MoveD(Game* game)
{ //move o jogador para baixo

    //muda a posiçao e direçao do jogaodr
    box.BoxAddY(1);
    dir = 0;

    //desfaz o movimento se o jogador colidir
    if (box.yf > 672 || game->zone[game->c.i-1][game->c.j-1].WallCheck(box))
        box.BoxAddY(-1);

    //faz a animação
    if (((int)box.yi)%50 <= 24)
        sprite = al_load_bitmap(".\\assets\\player_sprite_1.png");
    else sprite = al_load_bitmap(".\\assets\\player_sprite_0.png");

}

Player::Attack(Game* game, Instance* instance)
{ //realiza o ataque

    type = INV; //define o jogador como ivuneravel, para evitar bugs com hitbox

    //cria hitboxes auxiliares
    Hitbox aux = box;
    Hitbox sw;
    int i;

    //{ animação do ataque
    sprite = att_sprite[dir*4]; //primeiro estágio de ataque
    for(i=0; i<8; i++){ //faz a animação demorar mais
        UpdateGame(game, instance);
        al_wait_for_event(game->q, &game->ev);
    }

    sprite = att_sprite[dir*4+1]; //segundo estágio, cria uma hitbox de espada e verifica se acerta inimigos e corrige hitbox para animacao do ataque
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
    for(i=0; i<16; i++){ //faz a animiação demorar mais
        UpdateGame(game, instance);
        al_wait_for_event(game->q, &game->ev);
    }
    box = aux; //desfaz alterações da hitbox

    sprite = att_sprite[dir*4+2]; //terceiro estágio de ataque
    //corrige hitbox para animacao do ataque
    if (dir == 2){
      aux = box;
      box.yi -=33;
    }
    if (dir == 3){
      aux = box;
      box.xi -=21;
    }

    for(i=0; i<8; i++){ //faz a animiação demorar mais
        UpdateGame(game, instance);
        al_wait_for_event(game->q, &game->ev);
    }
    box = aux; //desfaz alterações da hitbox

    sprite = att_sprite[dir*4+3]; //quarto estágio de ataque
    //corrige hitbox para animacao do ataque
    if (dir == 2){
      aux = box;
      box.yi -=9;
    }
    if (dir == 3){
      aux = box;
      box.xi -=9;
    }

    for(i=0; i<8; i++){ //faz a animiação demorar mais
        UpdateGame(game, instance);
        al_wait_for_event(game->q, &game->ev);
    }
    box = aux; //desfaz alterações da hitbox
    //}

    //retorna o jogador para como estava antes
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

    //ativa o cooldown do ataque
    cd = 50;
}

Player::Save(Game* game)
{ //salva o progrsso do jogador

    //localiza o save do jogador
    std::ofstream file;
    if (save == 0)
        file.open(".\\assets\\save_0.txt");
    else if (save == 1)
        file.open(".\\assets\\save_1.txt");
    else if (save == 2)
        file.open(".\\assets\\save_2.txt");
    else return 0;

    // caso ele esteja na zona do boss, corrige isso
    if(game->c.i == 1 && game->c.j == 1){
        game->c.i = 2;
        box.xi = 384;
        box.yi = 366;
        box.xf = box.xi +47;
        box.yf = box.yi + 47;
    }

    //escreve no arquivo
    file << "registered = 1" << endl;
    file << "name = " << name << endl;
    file << "health = " << health << endl;
    file << "hitbox = " << box.xi << ", " << box.yi << endl;
    file << "zone = " << game->c.i << ", " << game->c.j << endl;
    file << "progress =  " << progress << endl;
    file << "arrow = " << a << endl;
    file << "rupee = " << r << endl;
    file.close();
}

Player::SwordCollision(Game* game, Hitbox sw)
{ //faz a colisão da espada do jogador
    //percorre o vetor de entidades
    for(int i = 0; i<game->zone[game->c.i-1][game->c.j-1].e.size(); i++){
        //se for um inimigo comum, desabilita ele e cria um drop
        if(sw.Collision(game->zone[game->c.i-1][game->c.j-1].e[i]->box) && game->zone[game->c.i-1][game->c.j-1].e[i]->type == TYPE_ENEMY){
            game->zone[game->c.i-1][game->c.j-1].e[i]->type = 0;
            Drop* d = new Drop(game->zone[game->c.i-1][game->c.j-1].e[i]->box);
            game->zone[game->c.i-1][game->c.j-1].e.push_back(d);
        }

        //se for um boss, diminui a vida dele
        if(sw.Collision(game->zone[game->c.i-1][game->c.j-1].e[i]->box) && game->zone[game->c.i-1][game->c.j-1].e[i]->type == TYPE_BOSS){
            game->zone[game->c.i-1][game->c.j-1].e[i]->health--;
        }
    }
}
