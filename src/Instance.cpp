#include "Header.h"

Instance::Instance()
{

    strt_background[0] = al_load_bitmap(".\\assets\\strt_background_0.png");
    strt_background[1] = al_load_bitmap(".\\assets\\strt_background_1.png");
    strt_background[2] = al_load_bitmap(".\\assets\\strt_background_2.png");

    load_background = al_load_bitmap(".\\assets\\load_background.png");
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

        if(game->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

			game->playing = false;

		}

        if(game->ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){

                game->playing = false;

            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ENTER){

                FileMenu(game);

                break;

            }

        }

        if(game->ev.type == ALLEGRO_EVENT_TIMER){

            al_draw_bitmap(strt_background[(i/3)%3], 0, 0, 0);
            al_flip_display();
            i++;

        }

    }

}

Instance::FileMenu(Game* game)
{

    std::cout << "Starting File Menu..." << std::endl;

    int x = 480, aux = 2, i=0;
    Player save[3];

    save[0].Load(".\\entities\\save_0.txt");
    save[1].Load(".\\entities\\save_1.txt");
    save[2].Load(".\\entities\\save_2.txt");

    if (save[0].registered == 1){x = 255;}
    else if (save[1].registered == 1) {x = 327;}
    else if (save[2].registered == 1) {x = 399;}

    if(save[0].registered == save[1].registered && save[0].registered == save[2].registered){

        if (save[0].registered == 1) {aux = 1;}
        else {aux = 0;}
    }

    while(game->playing){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){game->playing = false;}

        if(game->ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {StartMenu(game);}

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ENTER){

                if (x == 480) {RegisterMenu(game);}

                else if (x == 528) {EliminationMenu(game);}

                else if (x == 255) {

                    game->player = save[0];
                    MainGame(game);

                }

                else if (x == 327) {

                    game->player = save[1];
                    MainGame(game);

                }

                else if (x == 399) {

                    game->player = save[2];
                    MainGame(game);

                }

                save[0].Load(".\\entities\\save_0.txt");
                save[1].Load(".\\entities\\save_1.txt");
                save[2].Load(".\\entities\\save_2.txt");

            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_RIGHT || game->ev.keyboard.keycode == ALLEGRO_KEY_DOWN){

                if (x == 480 && aux != 0) {x = 528;}

                else if (x == 528){

                    if(save[0].registered == 1) {x = 255;}
                    else if(save[1].registered == 1) {x = 327;}
                    else if(save[2].registered == 1) {x = 399;}
                    else {x = 480;}

                }

                else if (x == 255){

                    if(save[1].registered == 1) {x = 327;}
                    else if(save[2].registered == 1) {x = 399;}
                    else {x = 480;}

                }

                else if (x == 327){

                    if(save[2].registered == 1) {x = 399;}
                    else {x = 480;}

                }

                else if(x == 399 ) {

                    if (aux != 1) {x = 480;}
                    else {x = 528;}

                }

            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_LEFT || game->ev.keyboard.keycode == ALLEGRO_KEY_UP){

                if (x == 480 && aux != 0){

                    if(save[2].registered == 1) {x = 399;}
                    else if(save[1].registered == 1) {x = 327;}
                    else if(save[0].registered == 1) {x = 255;}
                    else {x = 528;}

                }

                else if (x == 528) {

                    if (aux != 1) {x = 480;}
                    else {x = 399;}

                }

                else if (x == 255) {x = 528;}

                else if (x == 327) {

                    if(save[0].registered == 1) {x = 255;}
                    else {x = 528;}

                }

                else if(x == 399){

                    if(save[1].registered == 1) {x = 327;}
                    else if(save[0].registered == 1) {x = 255;}
                    else {x = 528;}

                }

            }

        }

        if(game->ev.type == ALLEGRO_EVENT_TIMER){

            al_draw_bitmap(load_background, 0, 0, 0);

            for(i = 0; i<3; i++){

                if(save[i].registered == 1) {al_draw_text(game->f, al_map_rgb(255,255,255), 216, i*72 + 240, 0, save[i].name);}

            }

            al_draw_bitmap(heart, 120, x, 0);

            al_flip_display();

        }

    }

}

Instance::RegisterMenu(Game* game)
{

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
    Load jogo;


    std::cout << jogo -> registered << std::endl;

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

