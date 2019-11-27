#include "Header.h"

Hitbox::BoxAddX(int x)
{

    this->xi+=x;
    this->xf+=x;

}

Hitbox::BoxAddY(int x)
{

    this->yi+=x;
    this->yf+=x;

}

bool Hitbox::Border()
{

    if(xi<=0)
        return true;
    else if (xf>=768)
        return true;
    else if (yf>=672)
        return true;
    else if (yi<=144)
        return true;
    else
        return false;

}

bool Hitbox::Collision(Hitbox box)
{

    if(this->xf+1 >= box.xi && this->xi-1 <= box.xi && this->yf+1 >= box.yi && this->yi-1 <= box.yf)
        return true;
    if(this->xi-1 <= box.xf && this->xf+1 >= box.xf && this->yf+1 >= box.yi && this->yi-1 <= box.yf)
        return true;
    if(this->yf+1 >= box.yi && this->yi-1 <= box.yi && this->xf+1 >= box.xi && this->xi-1 <= box.xf)
        return true;
    if(this->yi-1 <= box.yf && this->yi+1 >= box.yf && this->xf+1 >= box.xi && this->xi-1 <= box.xf)
        return true;
    else
        return false;

}
