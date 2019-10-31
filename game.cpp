#include "Base.h"


Game::Game()
{
    std::cout << "Initializing Game..." << std::endl;


    playing = true;

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
    t = al_create_timer(1.0/30);

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

    std::cout << "Game Closed!" << std::endl;

}

Game::InitCheck(){

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
