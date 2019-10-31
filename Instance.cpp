#include "Base.h"


Instance::Instance()
{

    strt_background[0] = al_load_bitmap(".\\assets\\strt_background_0.png");
    strt_background[1] = al_load_bitmap(".\\assets\\strt_background_1.png");
    strt_background[2] = al_load_bitmap(".\\assets\\strt_background_2.png");

}


Instance::~Instance()
{

    int i;

    for(i=0; i<3; i++){
        al_destroy_bitmap(strt_background[i]);
    }

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

    al_clear_to_color(al_map_rgb(0,0,0));
    al_flip_display();
    al_rest(1.0);


}
