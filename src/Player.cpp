#include "Header.h"

Player::Load(std::string file_path)
{

    std::ifstream save_file;

    save_file.open(file_path);

    save_file.ignore(100, '=');

    save_file >> name;

    save_file.ignore(100, '=');

    save_file >> max_health;

    save_file.ignore(100, '=');

    save_file >> health;

    save_file.ignore(100, '=');

    save_file >> hitbox.xi;

    save_file.ignore(100, ',');

    save_file >> hitbox.yi;

    save_file.ignore(100, '=');

    save_file >> i;

    save_file.ignore(100, ',');

    save_file >> j;

    std::cout << name << std::endl <<max_health << std::endl << health << std::endl << hitbox.xi << std::endl << hitbox.yi << std::endl << i << std::endl << j << std::endl ;




    save_file.close();

}


