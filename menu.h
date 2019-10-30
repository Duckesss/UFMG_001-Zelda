#include <allegro5/allegro.h>
#include <string>
using namespace std;

#ifndef _MENU_H
    #define _MENU_H

class Menu{
    private:
        string sprite;
    public:
        Menu(string sprite);
        void start();
        void load();
        void close();
};


#endif