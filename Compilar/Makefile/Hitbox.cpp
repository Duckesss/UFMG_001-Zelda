#include "Header.h"

Hitbox::BoxAddX(float x)
{

    this->xi+=x;
    this->xf+=x;

}

Hitbox::BoxAddY(float x)
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

    if(this->xf >= box.xi && this->xi <= box.xi && this->yf >= box.yi && this->yi <= box.yf)
        return true;
    if(this->xi <= box.xf && this->xf >= box.xf && this->yf >= box.yi && this->yi <= box.yf)
        return true;
    if(this->yf >= box.yi && this->yi <= box.yi && this->xf >= box.xi && this->xi <= box.xf)
        return true;
    if(this->yi <= box.yf && this->yf >= box.yf && this->xf >= box.xi && this->xi <= box.xf)
        return true;
    if (this->xi >= box.xi && this->xf <= box.xf && this->yi >= box.yi && this->yf <= box.yf)
        return true;
    else
        return false;

}
