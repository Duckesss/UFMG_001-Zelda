#include "Header.h"

//{declarações virtuais e destrutores
    Entity::Update(Game*, Instance*){}
    Entity::~Entity(){};
    Shooter::~Shooter(){};
    Runner::~Runner(){};
    Boss::~Boss(){};
    Bow::~Bow(){};
    Drop::~Drop(){};
    Projectile::~Projectile(){};
//}

Drop::Update(Game* game, Instance* instance)
{ //atualiza a entidade drop
    if(game->player->box.Collision(box) && game->player->type != INV){ //checa se o player entrou em contato com a entidade

        //faz o efeito dependendo do tipo e então desabilita a entidade
        if(type == TYPE_DROP_A)
            game->player->a++;
        if(type == TYPE_DROP_H)
            game->player->health+=2;
        if(type == TYPE_DROP_R)
            game->player->r++;
        type = 0;
    }
}

Drop::Drop(Hitbox box)
{ //cria o drop

    int r = (rand()%3)+6; //gera um numero aleatorio entre 6 e 8

    //define a posição do drop
    this->box.xi = box.xi;
    this->box.yi = box.yi;

    //conclui a criacao da hitbox do sprite dependendo do tipo gerado aleatrio
    if(r == TYPE_DROP_A){
        type = TYPE_DROP_A;
        this->box.xf = this->box.xi + 14;
        this->box.yf = this->box.yi + 47;
        sprite = al_load_bitmap(".\\assets\\arrow_2.png");
    }
    if(r == TYPE_DROP_H){
        type = TYPE_DROP_H;
        this->box.xf = this->box.xi + 23;
        this->box.yf = this->box.yi + 23;
        sprite = al_load_bitmap(".\\assets\\heart_0.png");
    }
    if(r == TYPE_DROP_R){
        type = TYPE_DROP_R;
        this->box.xf = this->box.xi + 15;
        this->box.yf = this->box.yi + 31;
        sprite = al_load_bitmap(".\\assets\\rupee.png");
    }
}

Projectile::Update(Game* game, Instance* instance)
{ //atualiza o projetil

    //move o projetil na velocidade v e o desabilita se ele colidir com alguma parede
    box.BoxAddX(v.x);
    box.BoxAddY(v.y);
    if(box.Border() || game->zone[game->c.i-1][game->c.j-1].WallCheck(box)){
        type = 0;
    }

    //checa se ele colidir com alguma entidade da zona
    for(int i=0; i<game->zone[game->c.i-1][game->c.j-1].e.size(); i++){
        if(this->box.Collision(game->zone[game->c.i-1][game->c.j-1].e[i]->box) && game->zone[game->c.i-1][game->c.j-1].e[i]->type != 0){
            //se for uma flecha acertando um inimigo, vai desabilitar ele, a flecha e criar um drop
            if (type == TYPE_PROJ && game->zone[game->c.i-1][game->c.j-1].e[i]->type == TYPE_ENEMY){
                game->zone[game->c.i-1][game->c.j-1].e[i]->type = 0;
                type = 0;
                Drop* d = new Drop(game->zone[game->c.i-1][game->c.j-1].e[i]->box);
                game->zone[game->c.i-1][game->c.j-1].e.push_back(d);
            }
            //se a flecha acertar o boss, desabilita a flecha e o boss perde vida
            if (type == TYPE_PROJ && game->zone[game->c.i-1][game->c.j-1].e[i]->type == TYPE_BOSS){
                type = 0;
                game->zone[game->c.i-1][game->c.j-1].e[i]->health--;
            }
        }
        //se o projétil for inimigo, ele vai diminuir a vida do player e alerta-lo do dano
        else if(this->box.Collision(game->player->box) && game->player->type != INV){
            if (type == TYPE_ENEMY){
                type = 0;
                al_clear_to_color(al_map_rgb(216,40,0));
                al_flip_display();
                game->player->health--;
                for(int wait = 0; wait < 5; wait++)
                    al_wait_for_event(game->q, &game->ev);
            }
        }
    }
}

Projectile::Arrow(Game* game)
{ //dispara uma flecha

    type = TYPE_PROJ;

    //{ define direções da flecha
    if(game->player->dir == 0){
        sprite = al_load_bitmap(".\\assets\\arrow_0.png");
        box.xi = game->player->box.xi + 21;
        box.xf = box.xi + 14;
        box.yi = game->player->box.yi + 49;
        box.yf = box.yi + 47;
        v.x = 0;
        v.y = 2;
    }
    else if(game->player->dir == 1){
        sprite = al_load_bitmap(".\\assets\\arrow_1.png");
        box.xi = game->player->box.xi + 49;
        box.xf = box.xi + 47;
        box.yi = game->player->box.yi + 18;
        box.yf = box.yi + 14;
        v.x = 2;
        v.y = 0;
    }
    else if(game->player->dir == 2){
        sprite = al_load_bitmap(".\\assets\\arrow_2.png");
        box.xi = game->player->box.xi + 9;
        box.xf = box.xi + 14;
        box.yi = game->player->box.yi - 49;
        box.yf = box.yi + 47;
        v.x = 0;
        v.y = -2;
    }
    else if(game->player->dir == 3){
        sprite = al_load_bitmap(".\\assets\\arrow_3.png");
        box.xi = game->player->box.xi - 49;
        box.xf = box.xi + 47;
        box.yi = game->player->box.yi + 18;
        box.yf = box.yi + 14;
        v.x = -2;
        v.y = 0;
    }
    //}

    //animação do tiro
    game->player->sprite = game->player->att_sprite[game->player->dir*4];
    al_draw_bitmap(sprite, box.xi, box.yi, 0);
    al_flip_display();
    al_wait_for_event(game->q, &game->ev);
    al_wait_for_event(game->q, &game->ev);

    //muda o cooldown da flecha
    game->player->cd_2 = 100;
}

Projectile::Ball(Hitbox box, int a)
{ // cria um projetil inimigo

    //define o tipo e a posicao do projetil
    type = TYPE_ENEMY;
    this->box.xi = box.xi + 12;
    this->box.xf = this->box.xi + 23;
    this->box.yi = box.yi + 12;
    this->box.yf = this->box.yi + 23;

    //muda o sprite dependendo do que for necessitado
    if (a == 0)
        sprite = al_load_bitmap(".\\assets\\ball_0_sprite.png");
    else if (a == 1)
        sprite = al_load_bitmap(".\\assets\\ball_1_sprite.png");
    else sprite = al_load_bitmap(".\\assets\\ball_2_sprite.png");
}

Bow::Update(Game* game, Instance* instance)
{ //atualiza o arco

    //verifica se o jogador entrou em contato cm o arco ou tem progresso = 1
    if((game->player->box.Collision(box) && game->c.i == 1 && game->c.j == 4) || game->player->progress == 1){
        type = 0;
        instance->map_background = al_load_bitmap(".\\assets\\map_background_1.png");
        instance->hud = al_load_bitmap(".\\assets\\hud_1.png");
        box.xi++;
        box.xf--;
        box.yi++;
        box.yf--;
        game->zone[0][3].wall.push_back(box);

        //all faz animação caso o jogador ainda não tiver pego o arco antes
        if (game->player->progress == 0){
            game->player->sprite = al_load_bitmap(".\\assets\\bow_sprite.png");
            al_draw_bitmap(instance->map_background, 0 - (game->c.j - 1)*768, 144 - (game->c.i - 1)*528, 0);
            al_draw_bitmap(instance->hud, 0, 0, 0);
            al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi-48, 0);
            al_flip_display();
            int i = 0;
            while(i < 500){
                al_wait_for_event(game->q, &game->ev);
                i++;
            }
            game->player->progress = 1;
            game->player->sprite = al_load_bitmap(".\\assets\\player_sprite_0.png");
        }
    }
}

Bow::Bow()
{ //cria o arco

    type = TYPE_BOW;
    box.xi = 384;
    box.yi = 339;
    box.xf = 431;
    box.yf = 386;
}

Shooter::Update(Game* game, Instance* instance)
{ //atualiza o atirador
    if(cd_2 == 0){ //checa se ele já pode atirar

        //cria projétil na direção do joador
        Projectile* ball = new Projectile();
        ball->Ball(box, 0);
        float dx = game->player->box.xi - box.xi;
        float dy = game->player->box.yi - box.yi;
        float hip = sqrt(pow(dx,2) + pow(dy,2));
        ball->v.x = 1.5*dx/hip;
        ball->v.y = 1.5*dy/hip;
        game->zone[game->c.i-1][game->c.j-1].e.push_back(ball);

        //atualiza os cooldowns e sua velocidade
        cd_2 = 400;
        cd+=50;
        v.x = 0;
        v.y = 0;
    }
    else if(cd == 0){ //checa se ele pode andar
        //gera uma direção aleatoria
        int r = rand();
        if(r%4==0){
            sprite = al_load_bitmap(".\\assets\\shooter_sprite_0.png");
            v.x = 0;
            v.y = 0.5;
        }
        if(r%4==1){
            sprite = al_load_bitmap(".\\assets\\shooter_sprite_1.png");
            v.x = 0.5;
            v.y = 0;
        }
        if(r%4==2){
            sprite = al_load_bitmap(".\\assets\\shooter_sprite_2.png");
            v.x = 0;
            v.y = -0.5;
        }
        if(r%4==3){
            sprite = al_load_bitmap(".\\assets\\shooter_sprite_3.png");
            v.x = -0.5;
            v.y = 0;
        }

        //atualiza seu cooldown
        cd = 300;
    }

    //move o atirador, se ele colidir com algo, reverte o movimento
    box.BoxAddX(v.x);
    box.BoxAddY(v.y);
    if(box.Border() || game->zone[game->c.i-1][game->c.j-1].WallCheck(box)){
        box.BoxAddX(-v.x);
        box.BoxAddY(-v.y);
    }

    //atualiza os cooldowns
    cd--;
    cd_2--;
    if(cd<0)
        cd = 0;
    if(cd_2<0)
        cd_2 = 0;
}

Shooter::Shooter(int x, int y)
{ //cria o atirador na posiçao x e y

    sprite = al_load_bitmap(".\\assets\\shooter_sprite_0.png");
    type = TYPE_ENEMY;
    box.xi = x;
    box.xf = box.xi+47;
    box.yi = y;
    box.yf = box.yi+47;
    v.x = 0;
    v.y = 0;
    cd = 1;
    cd = 0;
    cd_2 = 0;
}

Runner::Update(Game* game, Instance* instance)
{ //atualiza o runner

    //definicoes geometricas para calcular mais tarde
    float dx = game->player->box.xi - box.xi;
    float dy = game->player->box.yi - box.yi;
    float hip = sqrt(pow(dx,2) + pow(dy,2));

    //alcance da visao do runner
    if(hip < 150){
        cd = 0;
    }

    if (cd == 0 && cd_2 == 0){ //runner perseguindo

        v.x = .85*dx/hip; //vetor x da velocidade
        v.y = .85*dy/hip; //vetor y da velocidade

    }

    //se alcançou o jogador
    if(box.Collision(game->player->box) && game->player->type != INV && cd == 0){

        //dano
        al_clear_to_color(al_map_rgb(216,40,0));
        al_flip_display();
        game->player->health--;
        for(int wait = 0; wait < 5; wait++)
            al_wait_for_event(game->q, &game->ev);

        //recuo
        v.x = -5*dx/hip;
        v.y = -5*dy/hip;
        cd_2 = 30;
    }

    // animação de movimento
    if (((int)(box.xi+box.yi)%24 <= 11))
        sprite = al_load_bitmap(".\\assets\\runner_sprite_1.png");
    else sprite = al_load_bitmap(".\\assets\\runner_sprite_0.png");

    //movimenta o runner, se ele ultrapassar a borda, é desfeito
    box.BoxAddX(v.x);
    box.BoxAddY(v.y);
    if(box.Border()){
        box.BoxAddX(-v.x);
        box.BoxAddY(-v.y);
    }

    //atualiza os cooldowns
    cd_2--;
    if(cd_2<0)
        cd_2 = 0;
}

Runner::Runner(int x, int y)
{ //cria o atirador na posiçao x e y

    sprite = al_load_bitmap(".\\assets\\runner_sprite_1.png");
    type = TYPE_ENEMY;
    box.xi = x;
    box.xf = box.xi+31;
    box.yi = y;
    box.yf = box.yi+31;
    v.x = 0;
    v.y = 0;
    cd = 1;
    cd_2 = 0;
}

Boss::Update(Game* game, Instance* instance)
{ //atualiza o boss

    //checa se o boss ainda esta vivo
    if (health <= 0)
        type = 0;

    //define um novo estado
    if (cd == 0){
        state = rand()%3 + 1;
        cd = 100;
        cd_2 = 300;
    }

    //vai para o estado 0
    if (cd_2 == 0)
        state = 0;

    //reduz cd para ir para um novo estado
    if(state == 0){
        cd--;
        if (cd < 0)
            cd = 0;
    }

    //ataque "laser"
    else if (state == 1 && type != 0){

        //atira na direção do jogador
        Projectile* ball = new Projectile();
        ball->Ball(box, rand()%2 + 1);
        float dx = game->player->box.xi - box.xi;
        float dy = game->player->box.yi - box.yi;
        float hip = sqrt(pow(dx,2) + pow(dy,2));
        ball->v.x = 1.5*dx/hip;
        ball->v.y = 1.5*dy/hip;

        if(cd_2%60 == 0) //evita que muitas entidades
            game->zone[game->c.i-1][game->c.j-1].e.push_back(ball);

        //faz o boss ficar parado
        v.x = 0;
        v.y = 0;

        //atualiza cd_2
        cd_2--;
        if (cd_2 < 0)
            cd_2 = 0;

    }

    // ataque "aleatorio"
    else if (state == 2 && type != 0){

        //multiplicador negativo para poder criar um vetor em todas as direçoes
        int neg;

        //cria um projétil numa direção aleatoria
        if (rand()%2 == 0)
            neg = -1;
        else neg = 1;
        Projectile* ball = new Projectile();
        ball->Ball(box, rand()%2 + 1);
        ball->v.x = neg*((rand()%20)/10 + 1.5);
        if (rand()%2 == 0)
            neg = -1;
        else neg = 1;
        ball->v.y = neg*((rand()%20)/10 + 1.1);

        if(cd_2%20 == 0) //evita que crie muitos projéteis
            game->zone[game->c.i-1][game->c.j-1].e.push_back(ball);

        v.x = 0;
        v.y = 0;

        cd_2--;
        if (cd_2 < 0)
            cd_2 = 0;


    }
    else if (state == 3 && type != 0){
        if (cd_2 == 300){
            float dx = game->player->box.xi - box.xi;
            float dy = game->player->box.yi - box.yi;
            float hip = sqrt(pow(dx,2) + pow(dy,2));
            v.x = 3*dx/hip;
            v.y = 3*dy/hip;
            hit = 0;
        }

        box.BoxAddX(v.x);
        box.BoxAddY(v.y);

        if (game->zone[0][0].WallCheck(box)){
            box.BoxAddX(-v.x);
            box.BoxAddY(-v.y);
        }

        if(box.Collision(game->player->box) && game->player->type != INV && hit == 0){

            al_clear_to_color(al_map_rgb(216,40,0));
            al_flip_display();
            game->player->health--;
            for(int wait = 0; wait < 5; wait++)
                al_wait_for_event(game->q, &game->ev);
            hit = 1;

        }

        //atualiza o cooldown
        cd_2--;
        if (cd_2 <= 0){
            cd_2 = 0;
            box.xi = 96;
            box.yi = 375;
            box.xf = box.xi + 88;
            box.yf = box.yi + 95;
        }
    }
}

Boss::Boss()
{ //cria o boss

    health = 10;
    state = 0;
    box.xi = 96;
    box.yi = 375;
    box.xf = box.xi + 88;
    box.yf = box.yi + 95;
    type = TYPE_BOSS;
    v.x = 0;
    v.y = 0;
    cd = 30;
    cd_2 = 30;
    sprite = al_load_bitmap(".\\assets\\boss_sprite.png");
}



