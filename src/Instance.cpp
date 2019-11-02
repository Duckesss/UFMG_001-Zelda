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

    Player test;

    test.Load(".\\entities\\save_0.txt");


}

Instance::FileMenu(Game* game)
{

    std::cout << "Starting File Menu..." << std::endl;

    int x = 480;

    int loadedsaves[3];
    loadedsaves[0]=1;
    loadedsaves[1]=1;
    loadedsaves[2]=1;

    while(game->playing){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE){

			game->playing = false;

		}

        if(game->ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){

                StartMenu(game);

            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ENTER){

                if(x == 480){

                    RegisterMenu(game);

                }

                else if(x == 528){

                    EliminationMenu(game);

                }

            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_RIGHT || game->ev.keyboard.keycode == ALLEGRO_KEY_DOWN){

                if (x == 480){

                    x = 528;

                }

                else if (x == 528){

                    if(loadedsaves[0] == 1){

                        x = 255;

                    }

                    else if(loadedsaves[1] == 1){

                        x = 327;

                    }

                    else if(loadedsaves[2] == 1){

                        x = 399;

                    }

                    else{

                        x = 480;
                    }

                }

                else if (x == 255){

                    if(loadedsaves[1] == 1){

                        x = 327;

                    }

                    else if(loadedsaves[2] == 1){

                        x = 399;

                    }

                    else{

                        x = 480;

                    }

                }

                else if (x == 327){

                    if(loadedsaves[2] == 1){

                        x = 399;

                    }

                    else{

                        x = 480;

                    }

                }

                else if(x == 399){

                    x = 480;

                }

            }

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_LEFT || game->ev.keyboard.keycode == ALLEGRO_KEY_UP){

                if (x == 480){

                    if(loadedsaves[2] == 1){

                        x = 399;

                    }

                    else if(loadedsaves[1] == 1){

                        x = 327;

                    }

                    else if(loadedsaves[0] == 1){

                        x = 255;

                    }

                    else{

                        x = 528;
                    }

                }

                else if (x == 528){

                    x = 480;

                }

                else if (x == 255){

                    x = 528;

                }

                else if (x == 327){

                    if(loadedsaves[1] == 1){

                        x = 255;

                    }

                    else{

                        x = 528;

                    }

                }

                else if(x == 399){

                    if(loadedsaves[1] == 1){

                        x = 327;

                    }

                    else if(loadedsaves[0] == 1){

                        x = 255;

                    }

                    else{

                        x = 528;
                    }

                }

            }

        }

        if(game->ev.type == ALLEGRO_EVENT_TIMER){

            al_draw_bitmap(load_background, 0, 0, 0);

            al_draw_bitmap(heart, 120, x, 0);

            al_flip_display();

        }

    }

}

Instance::RegisterMenu(Game* game)
{

    while(game->playing){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){

                FileMenu(game);

            }

        }

        if(game->ev.type == ALLEGRO_EVENT_TIMER){

            al_draw_bitmap(register_background, 0, 0, 0);

            al_flip_display();

        }

    }

}

Instance::EliminationMenu(Game* game)
{

   while(game->playing){

        al_wait_for_event(game->q, &game->ev);

        if(game->ev.type == ALLEGRO_EVENT_KEY_DOWN){

            if(game->ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE){

                FileMenu(game);

            }

        }

        if(game->ev.type == ALLEGRO_EVENT_TIMER){

            al_draw_bitmap(elimination_background, 0, 0, 0);

            al_flip_display();

        }

    }

}
