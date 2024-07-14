#pragma once
#include <ncurses.h>

class Drawable {
public:
    Drawable() {
        y = x = 0;
        icon = ' ';
    }

    Drawable(int y, int x, chtype ch)
    {
        this->y = y;
        this->x = x;
        icon = ch;
    }

    int getX() const {
        return x;
    }
    int getY() const {
        return y;
    }

    chtype getIcon() const {  
        return icon; 
    }

protected:
    int y, x;
    chtype icon;
};
