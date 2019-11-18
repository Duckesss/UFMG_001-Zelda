#include "Header.h"

Instance::Instance()
{
    strt_background[0] = al_load_bitmap(".\\assets\\strt_background_0.png");
    strt_background[1] = al_load_bitmap(".\\assets\\strt_background_1.png");
    strt_background[2] = al_load_bitmap(".\\assets\\strt_background_2.png");

    load_background = al_load_bitmap(".\\assets\\load_background.png");

    dark_background = al_load_bitmap(".\\assets\\darkbackground.png");

    zelda_sprites[0] = al_load_bitmap(".\\assets\\movimentacao\\zelda0.png");
    zelda_sprites[1] = al_load_bitmap(".\\assets\\movimentacao\\zelda1.png");
    zelda_sprites[2] = al_load_bitmap(".\\assets\\movimentacao\\zelda2.png");
    zelda_sprites[3] = al_load_bitmap(".\\assets\\movimentacao\\zelda3.png");
    zelda_sprites[4] = al_load_bitmap(".\\assets\\movimentacao\\zelda4.png");
    zelda_sprites[5] = al_load_bitmap(".\\assets\\movimentacao\\zelda5.png");
    zelda_sprites[6] = al_load_bitmap(".\\assets\\movimentacao\\zelda6.png");
    zelda_sprites[7] = al_load_bitmap(".\\assets\\movimentacao\\zelda7.png");

    register_background = al_load_bitmap(".\\assets\\register_background.png");
    elimination_background = al_load_bitmap(".\\assets\\elimination_background.png");
    heart = al_load_bitmap(".\\assets\\heart.png");
}

Instance::~Instance()
{

    int i;

    for(i=0; i<3; i++){
        al_destroy_bitmap(strt_background[i]);
    }

    al_destroy_bitmap(load_background);

}

Instance::StartMenu(Game* game)
{
    int i = 0;
    std::cout << "Starting Menu..." << std::endl;
    while(game->playing){
        al_wait_for_event(game->q, &game->ev);
        this->quitGame(game,1);
        switch(game->ev.type){
            case ALLEGRO_EVENT_KEY_DOWN:
                if(game->ev.keyboard.keycode == ALLEGRO_KEY_ENTER)
                    FileMenu(game);
            break;
            case ALLEGRO_EVENT_TIMER:
                al_draw_bitmap(strt_background[(i/3)%3], 0, 0, 0);
                al_flip_display();
                i++;
            break;
        }
    }
}

Instance::FileMenu(Game* game)
{
    std::cout << "Starting File Menu..." << std::endl;
    int heartX = 3; // representa qual posição o coração está
    int aux = 2; // representa que nem todos estão no mesmo estado
    int i=0;
    Player save[3];
    save[0].Load(".\\entities\\save_0.txt");
    save[1].Load(".\\entities\\save_1.txt");
    save[2].Load(".\\entities\\save_2.txt");

    this->att_heartX(heartX,0,save,0);

    int cont = 0;
    for(int j=0;j<3;j++){
        if(save[j].registered == 1){
            cont++;
        }
    }
    if(cont == 3){  // se todos estão registrados
        aux = 1;
    }else if(cont == 0){    // se nenhum está registrado
        aux = 0;
    }

    while(game->playing){
        al_wait_for_event(game->q, &game->ev);
        switch(game->ev.type){
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                game->playing = false;
            break;
            case ALLEGRO_EVENT_KEY_DOWN:
                switch(game->ev.keyboard.keycode){
                    case ALLEGRO_KEY_ESCAPE:
                        StartMenu(game);
                    break;
                    case ALLEGRO_KEY_ENTER:
                        if (heartX == 3) {
                            RegisterMenu(game);
                        }
                        else if (heartX == 4) {
                            EliminationMenu(game);
                        }else{
                            game->player = save[heartX];
                            MainGame(game);
                        }
                        save[0].Load(".\\entities\\save_0.txt");
                        save[1].Load(".\\entities\\save_1.txt");
                        save[2].Load(".\\entities\\save_2.txt");
                    break;
                    // esses dois cases tem efeito de "ou"
                    case ALLEGRO_KEY_RIGHT:
                    case ALLEGRO_KEY_DOWN:
                            if (heartX == 3 && aux != 0) {    // vai do register para o elimination
                                heartX = 4;
                            }
                            else if (heartX == 4){
                                this->att_heartX(heartX,0,save,0);
                            }
                           else if (heartX == 0){
                                this->att_heartX(heartX,1,save,0);
                            }
                            else if (heartX == 1){
                                this->att_heartX(heartX,2,save,0);
                            }
                            else if(heartX == 2 ) {
                                if (aux != 1) {heartX = 3;}
                                else {heartX = 4;}
                            }
                    break;
                    // esses dois cases tem efeito de "ou"
                    case ALLEGRO_KEY_LEFT:
                    case ALLEGRO_KEY_UP:
                            if (heartX == 3 && aux != 0){
                            	this->att_heartX(heartX,2,save,1);
                            }
                            else if (heartX == 4) {
                                if (aux != 1){heartX = 3;}
                                else {heartX = 2;}
                            }
                            else if (heartX == 1) {
                            	this->att_heartX(heartX,0,save,1);
                            }
                            else if(heartX == 2){
                                this->att_heartX(heartX,1,save,1);
                            }else if(heartX == 0){
                                heartX = 4;
                            }
                    break;
                }
            break;
            case ALLEGRO_EVENT_TIMER:
                this->dicionario_heartX(heartX,0);    // manda o heartX para coordenadas
                al_draw_bitmap(load_background, 0, 0, 0);
                for(i = 0; i<3; i++){
                    if(save[i].registered == 1) {al_draw_text(game->f, al_map_rgb(255,255,255), 216, i*72 + 240, 0, save[i].name);}
                }
                al_draw_bitmap(heart, 120, heartX, 0);
                this->dicionario_heartX(heartX,1);        // manda o heartX para posições de volta
                al_flip_display();
            break;
        }
    }
}

Instance::RegisterMenu(Game* game)
{

    std::cout << "Registering..." << std::endl;
    Player save[3];
    save[0].Load(".\\entities\\save_0.txt");
    save[1].Load(".\\entities\\save_1.txt");
    save[2].Load(".\\entities\\save_2.txt");

    int x, i;
    if(save[0].registered == 0){x = 0;}
    else if (save[1].registered == 0) {x = 1;}
    else if (save[2].registered == 0) {x = 2;}

    while(game->playing){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {FileMenu(game);}

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ENTER){

                if (x == 3) {FileMenu(game);}
                else if (x == 0) {Register(game, ".\\entities\\save_0.txt", x);}
                else if (x == 1) {Register(game, ".\\entities\\save_1.txt", x);}
                else if (x == 2) {Register(game, ".\\entities\\save_2.txt", x);}

                save[0].Load(".\\entities\\save_0.txt");
                save[1].Load(".\\entities\\save_1.txt");
                save[2].Load(".\\entities\\save_2.txt");

                if(save[0].registered == 0){x = 0;}
                else if (save[1].registered == 0) {x = 1;}
                else if (save[2].registered == 0) {x = 2;}
                else {x = 3;}

            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_RIGHT || game->ev.keyboard.keycode == ALLEGRO_KEY_DOWN){

                if(x == 0) {

                    if (save[1].registered == 0) {x = 1;}
                    else if (save[2].registered == 0) {x = 2;}
                    else {x = 3;}

                }

                else if(x == 1) {

                    if (save[2].registered == 0) {x = 2;}
                    else {x = 3;}

                }

                else if(x == 2) {x = 3;}

                else if(x == 3){

                    if(save[0].registered == 0){x = 0;}
                    else if (save[1].registered == 0) {x = 1;}
                    else if (save[2].registered == 0) {x = 2;}

                }

            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_LEFT || game->ev.keyboard.keycode == ALLEGRO_KEY_UP){


                if(x == 0) {x = 3;}

                else if(x == 1) {

                    if(save[0].registered == 0) {x = 0;}
                    else {x = 3;}

                }

                else if(x == 2){

                    if (save[1].registered == 0) {x = 1;}
                    else if(save[0].registered == 0) {x = 0;}
                    else {x = 3;}

                }

                else if(x == 3){

                    if (save[2].registered == 0) {x = 2;}
                    else if (save[1].registered == 0) {x = 1;}
                    else if(save[0].registered == 0) {x = 0;}
                    else {x = 3;}

                }

            }



        }

        if(game->ev.type == ALLEGRO_EVENT_TIMER){

            al_draw_bitmap(register_background, 0, 0, 0);
            al_draw_bitmap(heart, 201, x*72 + 120, 0);

            for(i = 0; i<3; i++){

                if(save[i].registered == 1) {al_draw_text(game->f, al_map_rgb(255,255,255), 336, i*72 + 120, 0, save[i].name);}

            }

            al_flip_display();

        }

    }

}

Instance::EliminationMenu(Game* game)
{

    Player save[3];

    save[0].Load(".\\entities\\save_0.txt");
    save[1].Load(".\\entities\\save_1.txt");
    save[2].Load(".\\entities\\save_2.txt");

    int x, i;

    if(save[2].registered == 1){x = 0;}
    else if (save[1].registered == 1) {x = 1;}
    else if (save[0].registered == 1) {x = 2;}

    while(game->playing){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {FileMenu(game);}

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ENTER){

                if (x == 3) {FileMenu(game);}

                else if (x == 0){

                    std::ofstream save;
                    save.open(".\\entities\\save_0.txt");

                    save << "registered = 0" << std::endl;
                    save << "name = link " << std::endl;
                    save << "health = 3" << std::endl;
                    save << "hitbox = 0, 0" << std::endl;
                    save << "zone = 1, 2" << std:: endl;

                    save.close();

                }

                else if (x == 1){

                    std::ofstream save;
                    save.open(".\\entities\\save_1.txt");

                    save << "registered = 0" << std::endl;
                    save << "name = link " << std::endl;
                    save << "health = 3" << std::endl;
                    save << "hitbox = 0, 0" << std::endl;
                    save << "zone = 1, 2" << std:: endl;

                    save.close();

                }

                else if (x == 2){

                    std::ofstream save;
                    save.open(".\\entities\\save_2.txt");

                    save << "registered = 0" << std::endl;
                    save << "name = link " << std::endl;
                    save << "health = 3" << std::endl;
                    save << "hitbox = 0, 0" << std::endl;
                    save << "zone = 1, 2" << std:: endl;

                    save.close();

                }

                save[0].Load(".\\entities\\save_0.txt");
                save[1].Load(".\\entities\\save_1.txt");
                save[2].Load(".\\entities\\save_2.txt");

                if(save[0].registered == 1){x = 0;}
                else if (save[1].registered == 1) {x = 1;}
                else if (save[2].registered == 1) {x = 2;}
                else {x = 3;}

            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_RIGHT || game->ev.keyboard.keycode == ALLEGRO_KEY_DOWN){

                if(x == 0) {

                    if (save[1].registered == 1) {x = 1;}
                    else if (save[2].registered == 1) {x = 2;}
                    else {x = 3;}

                }

                else if(x == 1) {

                    if (save[2].registered == 1) {x = 2;}
                    else {x = 3;}

                }

                else if(x == 2) {x = 3;}

                else if(x == 3){

                    if(save[0].registered == 1){x = 0;}
                    else if (save[1].registered == 1) {x = 1;}
                    else if (save[2].registered == 1) {x = 2;}

                }

            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_LEFT || game->ev.keyboard.keycode == ALLEGRO_KEY_UP){


                if(x == 0) {x = 3;}

                else if(x == 1) {

                    if(save[0].registered == 1) {x = 0;}
                    else {x = 3;}

                }

                else if(x == 2){

                    if (save[1].registered == 1) {x = 1;}
                    else if(save[0].registered == 1) {x = 0;}
                    else {x = 3;}

                }

                else if(x == 3){

                    if (save[2].registered == 1) {x = 2;}
                    else if (save[1].registered == 1) {x = 1;}
                    else if(save[0].registered == 1) {x = 0;}
                    else {x = 3;}

                }

            }



        }

        if(game->ev.type == ALLEGRO_EVENT_TIMER){

            al_draw_bitmap(elimination_background, 0, 0, 0);
            al_draw_bitmap(heart, 201, x*72 + 120, 0);

            for(i = 0; i<3; i++){

                if(save[i].registered == 1) {al_draw_text(game->f, al_map_rgb(255,255,255), 336, i*72 + 120, 0, save[i].name);}

            }

            al_flip_display();

        }

    }

}

Instance::MainGame(Game* game)
{
    //Load jogo;
    //std::cout << jogo -> registered << std::endl;

    this->gameLoop(game);
    std::cout << "!!!" << std::endl;

}

Instance::gameLoop(Game* game)
{
    int position_to_render = 2;
    int x = 0;
    int y = 0;
    al_draw_bitmap(dark_background, 0, 0, 0);
    al_draw_bitmap(zelda_sprites[position_to_render], y, x, 0);
    while(game->playing){
        al_wait_for_event(game->q, &game->ev);
        this->quitGame(game,1);
        switch(game->ev.type){
            case ALLEGRO_EVENT_KEY_DOWN:
                switch(game->ev.keyboard.keycode){
                    case ALLEGRO_KEY_UP:
                        if(y-20 >= 0)
                        y-=20;
                        position_to_render = position_to_render == 0? 1 : 0;
                    break;
                    case ALLEGRO_KEY_DOWN:
                        if(y+20 <= 630)
                        y+=20;
                        position_to_render = position_to_render == 2? 3 : 2;
                    break;
                    case ALLEGRO_KEY_LEFT:
                        if(x-20 >= 0)
                        x-=20;
                        position_to_render = position_to_render == 6? 7 : 6;
                    break;
                    case ALLEGRO_KEY_RIGHT:
                        if(x+20 <= 720)
                        x+=20;
                        position_to_render = position_to_render == 4? 5 : 4;
                    break;
                }
            break;
            case ALLEGRO_EVENT_TIMER:
                al_draw_bitmap(dark_background, 0, 0, 0);
                al_draw_bitmap(zelda_sprites[position_to_render], x, y, 0);
                al_flip_display();
            break;
        }
    }
}

Instance::Register(Game* game, std::string save_dir, int y)
{
    char name[9];
    int i;
    bool aux = true, reg = true;

    for(i=0; i<9; i++){

        name[i] = '_';

    }

    i = 0;

    name[8] = '\0';

    while (aux){

        al_draw_bitmap(register_background, 0, 0, 0);
        al_draw_text(game->f, al_map_rgb(255,255,255), 336, y*72 + 120, 0, name);
        al_flip_display();

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_KEY_CHAR && game->ev.keyboard.keycode != ALLEGRO_KEY_ENTER && game->ev.keyboard.keycode != ALLEGRO_KEY_BACKSPACE && game->ev.keyboard.keycode != ALLEGRO_KEY_ESCAPE){

            name[i] = game->ev.keyboard.unichar;

            if(i<7){i++;}

        }

        else if (game->ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){
                name[i] = '_';
                i--;
                name[i] = '_';
            }

            else if(game->ev.keyboard.keycode == ALLEGRO_KEY_ENTER){
                if(i==7) {i++;}
                name[i] = '\0';
                aux = false;
            }

            else if(game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                aux = false;
                reg = false;
                RegisterMenu(game);
            }

        }

    }

    if (reg){
        std::ofstream save;
        save.open(save_dir);
        save << "registered = 1" << std::endl;
        save << "name = " << name << std::endl;
        save << "health = 3" << std::endl;
        save << "hitbox = 0, 0" << std::endl;
        save << "zone = 1, 2" << std:: endl;
        save.close();
    }
}

Instance::dicionario_heartX(int &heartX, int coordenadas)
{
    if(!coordenadas){
        // dicionario que transforma a posição do coração em coordenadas
        switch(heartX){
            case 0:
                heartX = 255;   // primeira opcao
            break;
            case 1:
                heartX = 327; // segunda opcao
            break;
            case 2:
                heartX = 399; // terceira opcao
            break;
            case 3:
                heartX = 480; // register menu
            break;
            case 4:
                heartX = 528; // elimination menu
            break;
        }
    }else{
        // dicionario que transforma as coordenadas do coração em posições
        switch(heartX){
            case 255:
                heartX = 0;   // primeira opcao
            break;
            case 327:
                heartX = 1; // segunda opcao
            break;
            case 399:
                heartX = 2; // terceira opcao
            break;
            case 480:
                heartX = 3; // register menu
            break;
            case 528:
                heartX = 4; // elimination menu
            break;
        }
    }
}

Instance::att_heartX(int &heartX,int posicao,Player save[], int decrease)
{
    int entrou = 0;
    if(decrease){
        for(int j=posicao;j>-1;j--){
            if(save[j].registered == 1) {
                entrou = 1;
                heartX = j;
                break;  // para no primeiro que achar
            }
        }
    }else{
        for(int j=posicao;j<3;j++){
            if(save[j].registered == 1) {
                entrou = 1;
                heartX = j;
                break;  // para no primeiro que achar
            }
        }
    }
    if(!entrou){
    	if(decrease){
    		heartX = 4; // elimination
    	}else{
    		heartX = 3; // register
    	}
    }
}
Instance::quitGame(Game* game,int hasEventQueue)
{
    if(hasEventQueue == 0)
        al_wait_for_event(game->q, &game->ev);

    switch(game->ev.type){
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            game->playing = false;
        break;
        case ALLEGRO_EVENT_KEY_DOWN:
            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){
                game->playing = false;
            }
        break;
    }
}
