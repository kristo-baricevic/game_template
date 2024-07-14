#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

class Character : public Drawable
{
    public:
    Character(int y, int x)
    {
        this->y = y;
        this->x = x;
        this->icon = 'A';
    }
};