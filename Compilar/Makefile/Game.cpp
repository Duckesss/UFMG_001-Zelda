#include "Header.h"

Game::Game()
{
    std::cout << "Initializing Game..." << std::endl;

    playing = true;
    running = true;

    al_init();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_keyboard();
	al_install_audio();
	al_init_acodec_addon();
  al_reserve_samples(7);

    d = al_create_display(768,672);
    q = al_create_event_queue();
    t = al_create_timer(1.0/150);


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

    for (i=0; i<7; i++){
        for(int j = 0; j<3; j++){
            for(int k = 0; k<zone[i][j].e.size(); k++){
                al_destroy_bitmap(zone[i][j].e[k]->sprite);
                delete zone[i][j].e[k];
            }
        }
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

Game::LoadZones()
{

    for (int i=0; i<3; i++){
        for(int j = 0; j<7; j++){
            zone[i][j].e.clear();
        }
    }

    //{ Carrega as paredes da zona
        zone[1][0].Load(".\\assets\\zone_0.txt");
        zone[1][1].Load(".\\assets\\zone_1.txt");
        zone[1][2].Load(".\\assets\\zone_2.txt");
        zone[1][3].Load(".\\assets\\zone_3.txt");
        zone[1][4].Load(".\\assets\\zone_5.txt");
        zone[1][5].Load(".\\assets\\zone_6.txt");
        zone[1][6].Load(".\\assets\\zone_7.txt");
        zone[0][1].Load(".\\assets\\zone_9.txt");
        zone[0][3].Load(".\\assets\\zone_4.txt");
        zone[2][6].Load(".\\assets\\zone_8.txt");
        zone[0][0].Load(".\\assets\\zone_9.txt");
    //}

    Bow* bow = new Bow();
    zone[0][3].e.push_back(bow);

    Shooter* s_0 = new Shooter(600, 250);
    Shooter* s_1 = new Shooter(150, 400);
    zone[1][6].e.push_back(s_0);
    zone[1][6].e.push_back(s_1);

    Shooter* s_2 = new Shooter(440, 200);
    Shooter* s_3 = new Shooter(300, 560);
    zone[1][5].e.push_back(s_2);
    zone[1][5].e.push_back(s_3);

    Runner* r_0 = new Runner(300,300);
    Runner* r_1 = new Runner(300,450);
    zone[1][4].e.push_back(r_0);
    zone[1][4].e.push_back(r_1);

    Runner* r_2 = new Runner(125,500);
    Runner* r_3 = new Runner(600,500);
    zone[1][3].e.push_back(r_2);
    zone[1][3].e.push_back(r_3);

    Shooter* s_4 = new Shooter(225, 200);
    Shooter* s_5 = new Shooter(260, 560);
    Runner* r_4 = new Runner(580, 200);
    zone[1][2].e.push_back(s_5);
    zone[1][2].e.push_back(s_4);
    zone[1][2].e.push_back(r_4);

    Shooter* s_6 = new Shooter(100, 200);
    Shooter* s_7 = new Shooter(300, 200);
    Shooter* s_8 = new Shooter(500, 200);
    zone[1][1].e.push_back(s_6);
    zone[1][1].e.push_back(s_7);
    zone[1][1].e.push_back(s_8);

    Boss* boss = new Boss();
    zone[0][0].e.push_back(boss);




}
