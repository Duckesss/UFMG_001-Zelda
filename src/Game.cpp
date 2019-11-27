#include "Header.h"

Game::Game()
{
    std::cout << "Initializing Game..." << std::endl;

    playing = true;

    acd = 0;
    scd = 0;

    LoadZones();

    al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();

    d = al_create_display(768,672);
    q = al_create_event_queue();
    t = al_create_timer(1.0/150);
    f = al_load_ttf_font(".\\assets\\font.ttf", 24, 0);

    al_register_event_source(q, al_get_keyboard_event_source());
	al_register_event_source(q, al_get_display_event_source(d));
	al_register_event_source(q, al_get_timer_event_source(t));

    al_start_timer(t);

    InitCheck();

}

Game::~Game()
{

    std::cout << "Closing Game..." << std::endl;

    al_uninstall_audio();
    al_uninstall_keyboard();

    al_destroy_display(d);
    al_destroy_timer(t);
    al_destroy_event_queue(q);

    al_destroy_bitmap(player->sprite);

    std::cout << "Game Closed!" << std::endl;

    int i;

    for (i=0; i<16; i++){

        al_destroy_bitmap(player->att_sprite[i]);

    }

    for (i=0; i<30; i++){

        al_destroy_bitmap(p[i].sprite);

    }

}

Game::InitCheck()
{

    std::cout << "Verifying Initialization" << std::endl;

    if(!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	if(!al_init_ttf_addon()) {
		fprintf(stderr, "failed to initialize tft addon!\n");
		return -1;
	}

	if(!al_init_image_addon()) {
		fprintf(stderr, "failed to initialize image addon!\n");
		return -1;
	}

	if(!al_init_acodec_addon()) {
		fprintf(stderr, "failed to initialize acodec addon!\n");
		return -1;
	}

	if(!al_init_primitives_addon()){
		fprintf(stderr, "failed to initialize primitives!\n");
        return -1;
    }

	if(!al_install_keyboard()){
		fprintf(stderr, "failed to initialize keyboard!\n");
		return -1;
	}

	if(!al_install_audio()){
        fprintf(stderr, "failed to initialize audio!\n");
		return -1;
	}

	if(!t) {
      fprintf(stderr, "failed to create timer!\n");
      return -1;
   }

	if(!q) {
      fprintf(stderr, "failed to create event_queue!\n");
      return -1;
	}

	if(!d) {
      fprintf(stderr, "failed to create display!\n");
      return -1;
   }

   std::cout << "Game Initialized Successfully!" << std::endl;

	return 1;

}

bool Game::WallCheck(Hitbox box)
{

    int i;

    for(i = 0; i<zone[c.i-1][c.j-1].wall.size(); i++){
        if(box.Collision(zone[c.i-1][c.j-1].wall[i]))
            return true;
    }

    return false;

}

Game::LoadZones()
{

    zone[1][0].Load(".\\assets\\zone_0.txt");

    Bow bow = Bow();

    zone[0][3].bow = bow;
}
