#include "Header.h"

Instance::Instance()
{
    strt_background[0] = al_load_bitmap(".\\assets\\strt_background_0.png");
    strt_background[1] = al_load_bitmap(".\\assets\\strt_background_1.png");
    strt_background[2] = al_load_bitmap(".\\assets\\strt_background_2.png");


    load_background = al_load_bitmap(".\\assets\\load_background.png");
    pause_screen = al_load_bitmap(".\\assets\\pause_screen.png");
    register_background = al_load_bitmap(".\\assets\\register_background.png");
    elimination_background = al_load_bitmap(".\\assets\\elimination_background.png");
    map_background = al_load_bitmap(".\\assets\\map_background_0.png");
    hud = al_load_bitmap(".\\assets\\hud_0.png");
    defeat_background = al_load_bitmap(".\\assets\\defeat_background.png");
    victory_background = al_load_bitmap(".\\assets\\victory_background.png");

    heart = al_load_bitmap(".\\assets\\heart_0.png");
    half_heart = al_load_bitmap(".\\assets\\heart_1.png");
    empty_heart = al_load_bitmap(".\\assets\\heart_2.png");
    f = al_load_ttf_font(".\\assets\\font.ttf", 24, 0);
    f_1 = al_load_ttf_font(".\\assets\\font.ttf", 48, 0);
    f_2 = al_load_ttf_font(".\\assets\\font.ttf", 72, 0);
    musica1 = al_load_audio_stream("menu.ogg", 4, 1024);


}

Instance::~Instance()
{

    int i;

    for(i=0; i<3; i++){
        al_destroy_bitmap(strt_background[i]);
    }

    al_destroy_bitmap(load_background);
    al_destroy_bitmap(register_background);
    al_destroy_bitmap(elimination_background);
    al_destroy_bitmap(map_background);
    al_destroy_bitmap(hud);
    al_destroy_bitmap(heart);

}

Instance::StartMenu(Game* game)
{
    float i = 0;
    al_attach_audio_stream_to_mixer(musica1, al_get_default_mixer());
    al_set_audio_stream_playmode(musica1, ALLEGRO_PLAYMODE_LOOP);

    std::cout << "Starting Menu..." << std::endl;

    while(game->running){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

			game->running = false;
			game->playing = false;

		}

        if(game->ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){

                game->running = false;
                game->playing = false;

            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ENTER){

                FileMenu(game);

                break;

            }

        }


        if(game->ev.type == ALLEGRO_EVENT_TIMER){

            al_draw_bitmap(strt_background[((int)i/3)%3], 0, 0, 0);
            al_flip_display();
            i+=0.1;

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

    while(game->running){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

			game->running = false;
			game->playing = false;

        }

        if(game->ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {StartMenu(game);}

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ENTER){

                game->playing = true;

                if (x == 480) {RegisterMenu(game);}

                else if (x == 528) {EliminationMenu(game);}

                else if (x == 255) {

                    game->player = &save[0];
                    game->player->save = 0;
                    game->c = game->player->c;

                    MainGame(game);

                }

                else if (x == 327) {

                    game->player = &save[1];
                    game->player->save = 1;
                    game->c = game->player->c;
                    MainGame(game);

                }

                else if (x == 399) {

                    game->player = &save[2];
                    game->player->save = 2;
                    game->c = game->player->c;
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
                if(save[i].registered == 1){
                    al_draw_text(f, al_map_rgb(255,255,255), 216, i*72 + 240, 0, save[i].name);
                    DisplayHealth(save[i].health, 432, 240 + i*72);
                }

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

    while(game->running){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

			game->running = false;
			game->playing = false;

		}

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

                if(save[i].registered == 1) {al_draw_text(f, al_map_rgb(255,255,255), 336, i*72 + 120, 0, save[i].name);}

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

    if(save[2].registered == 1){x = 2;}
    else if (save[1].registered == 1) {x = 1;}
    else if (save[0].registered == 1) {x = 0;}

    while(game->running){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

			game->running = false;
			game->playing = false;

		}

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

                if(save[i].registered == 1)
                    al_draw_text(f, al_map_rgb(255,255,255), 336, i*72 + 120, 0, save[i].name);

            }

            al_flip_display();

        }

    }

}

Instance::MainGame(Game* game)
{

    game->LoadZones();

    game->player->cd = 0;
    game->player->cd_2 = 0;
    int i;
    bool aux;

    ALLEGRO_KEYBOARD_STATE key;
    al_get_keyboard_state(&key);

    game->player->dir = 0;

    if (game->player->progress == 1)
        for(i = 0; i<game->zone[0][3].e.size(); i++)
            if (game->zone[0][3].e[i]->type == TYPE_BOW)
                    game->zone[0][3].e[i]->Update(game, this);

    if (game->player->progress == 0){
        map_background = al_load_bitmap(".\\assets\\map_background_0.png");
        hud = al_load_bitmap(".\\assets\\hud_0.png");
    }

    while(game->playing){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

			game->running = false;
			game->playing = false;

		}

        if(game->ev.type == ALLEGRO_EVENT_TIMER){

            if(game->player->box.Border()){
                if(game->player->box.xf >= 768)
                    game->zone[game->c.i][game->c.j].MoveR(game, this);
                if(game->player->box.xi <= 0)
                    game->zone[game->c.i][game->c.j].MoveL(game, this);
                if(game->player->box.yi <= 144)
                    game->zone[game->c.i][game->c.j].MoveU(game, this);
                if(game->player->box.yf >= 672)
                    game->zone[game->c.i][game->c.j].MoveD(game, this);
                Check(game, this);
            }

            if(al_key_down(&key, ALLEGRO_KEY_RIGHT))
                game->player->MoveR(game);
            if (al_key_down(&key, ALLEGRO_KEY_LEFT))
                game->player->MoveL(game);
            if(al_key_down(&key, ALLEGRO_KEY_DOWN))
                game->player->MoveD(game);
            if (al_key_down(&key, ALLEGRO_KEY_UP))
                game->player->MoveU(game);
            if (al_key_down(&key, ALLEGRO_KEY_X)&&game->player->cd==0)
                game->player->Attack(game, this);
            else if (al_key_down(&key, ALLEGRO_KEY_Z)&&game->player->cd_2==0&&game->player->progress == 1&&game->player->a > 0){
                Projectile* arrow = new Projectile;
                game->player->a--;
                arrow->Arrow(game);
                game->zone[game->c.i-1][game->c.j-1].e.push_back(arrow);
            }
            if (al_key_down(&key, ALLEGRO_KEY_ESCAPE))
                PauseScreen(game);

            UpdateGame(game, this);
            al_get_keyboard_state(&key);

            if(game->player->health <= 0)
                Defeat(game);

            if (game->zone[0][0].e[0]->health == 0)
                Victory(game);

        }
    }

    if (!game->playing && game->running)
        StartMenu(game);

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
        al_draw_text(f, al_map_rgb(255,255,255), 336, y*72 + 120, 0, name);
        al_flip_display();

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

            aux = false;
			game->running = false;
			game->playing = false;

		}

        if(game->ev.type == ALLEGRO_EVENT_KEY_CHAR && game->ev.keyboard.keycode != ALLEGRO_KEY_ENTER && game->ev.keyboard.keycode != ALLEGRO_KEY_BACKSPACE && game->ev.keyboard.keycode != ALLEGRO_KEY_ESCAPE){

            if(i<8 && ((game->ev.keyboard.unichar >= 65 && game->ev.keyboard.unichar <= 90) || (game->ev.keyboard.unichar >= 97 && game->ev.keyboard.unichar <= 122))){

                name[i] = game->ev.keyboard.unichar;
                i++;

            }

        }

        else if (game->ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_BACKSPACE){

                if(i<8) {name[i] = '_';}

                i--;
                name[i] = '_';

                if(i<0) { i = 0;}

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
        save << "health = 6" << std::endl;
        save << "hitbox = 360, 516" << std::endl;
        save << "zone = 3, 7" << std::endl;
        save << "progress = 0" << std::endl;
        save << "arrow = 10" << std::endl;
        save << "rupee = 0" << std::endl;

        save.close();

    }

}

Instance::PauseScreen(Game* game)
{

    int y = 0;
    int x = 0;
    bool pause = true;
    game->player->Save(game);

    while (pause){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

            pause = false;
			game->running = false;
			game->playing = false;

		}

        if(game->ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_RIGHT || game->ev.keyboard.keycode == ALLEGRO_KEY_DOWN){
                x++;

                if (x>1)
                    x = 1;

            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_LEFT || game->ev.keyboard.keycode == ALLEGRO_KEY_UP){
                x--;

                if (x<0)
                    x = 0;
            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ENTER){

                if(x == 0){
                    pause = false;
                }

                else if (x == 1){

                    game->playing = false;
                    pause = false;

                }

            }

        }

        if(game->ev.type == ALLEGRO_EVENT_TIMER){

            al_draw_bitmap(map_background, 0 - (game->c.j - 1)*MAP_X, 144 - (game->c.i - 1)*MAP_Y, 0);
            al_draw_bitmap(hud, 0, 0, 0);
            al_draw_bitmap(game->player->sprite, game->player->box.xi, game->player->box.yi, 0);
            al_draw_bitmap(pause_screen, 0, 0, 0);
            al_draw_bitmap(heart, 240 + x*48, 300 + x*100, 0);
            al_draw_text(f_2, al_map_rgb(255,255,255), 384, 36, ALLEGRO_ALIGN_CENTRE, "PAUSE");
            al_draw_text(f, al_map_rgb(255,255,255), 384, 300, ALLEGRO_ALIGN_CENTRE, "CONTINUE");
            al_draw_text(f, al_map_rgb(255,255,255), 384, 400,  ALLEGRO_ALIGN_CENTRE, "QUIT");
            al_flip_display();

        }


    }

}

Instance::DisplayHealth(int health, int x, int y)
{

    int h[8];
    int i = 0;

    for(i=0; i<8; i++)
        h[i] = 0;

    i = 0;

    while (health >0){

        if (h[i] != 2){
            health--;
            h[i]++;
        }

        else
            i++;
    }

    i = 0;

    for(i=0; i<8; i++){

        if(h[i] == 2)
            al_draw_bitmap(heart, x+24*i, y, 0);
        else if(h[i] == 1)
            al_draw_bitmap(half_heart, x+24*i, y, 0);
        else
            al_draw_bitmap(empty_heart, x+24*i, y, 0);

    }

}

Instance::DisplayNum(int num, int x, int y)
{

    int v[3];
    int i=0;
    char txt[10][10];

    for (i=0; i<3; i++)
        v[i] = 0;

    i = 0;

    while(num > 0){

        if (num >= pow(10,(2-i))){
            num -= pow(10,(2-i));
            v[i]++;
        }
        else if (num < pow(10,(2-i)))
            i++;
    }

    for (i=0; i<3; i++){
        sprintf(txt[i], "%d", v[i]);
        al_draw_text(f, al_map_rgb(255,255,255), x + 24*i, y, 0, txt[i]);
    }


}

Instance::Defeat(Game* game)
{

    al_set_audio_stream_playing(musica1,0);
    bool aux = true;

    game->playing = false;

    al_draw_bitmap(defeat_background, 0, 0, 0);

    al_draw_text(f_2, al_map_rgb(255,255,255), 384, 36, ALLEGRO_ALIGN_CENTRE, "REPROVADO");

    al_flip_display();

    while(aux){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

            aux = false;
			game->running = false;
			game->playing = false;

		}

        if(game->ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ENTER || game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                aux = false;
        }

    }

}

Instance::Victory(Game* game)
{
    al_set_audio_stream_playing(musica1,0);
    bool aux = true;

    game->playing = false;

    al_draw_bitmap(victory_background, 0, 0, 0);

    al_draw_text(f_2, al_map_rgb(255,255,255), 384, 36, ALLEGRO_ALIGN_CENTRE, "APROVADO");

    al_flip_display();

    game->player->Save(game);

    while(aux){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

            aux = false;
			game->running = false;
			game->playing = false;

		}

        if(game->ev.type == ALLEGRO_EVENT_KEY_DOWN){
            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ENTER || game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                aux = false;
        }

    }

}
