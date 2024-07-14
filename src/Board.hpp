#pragma once
#include <ncurses.h>
#include <iostream>
#include "Drawable.hpp"

class Board
{
public:
    Board()
    {
        construct(20, 40); // Default dimensions for default constructor
    }

    Board(int height, int width)
    {
        construct(height, width);
    }

    void initialize()
    {
        wclear(board_win);
        addBorder();
        wrefresh(board_win);
    }

    void addBorder()
    {
        box(board_win, 0, 0);
    }

    void add(Drawable drawable) {
        addAt(drawable.getY(), drawable.getX(), drawable.getIcon());
    }

    void addAt(int y, int x, chtype ch)
    {
        mvwaddch(board_win, y, x, ch);
        wrefresh(board_win);
    }

    chtype getInput()
    {
        return wgetch(board_win);
    }

    void getEmptyCoordinates(int& y, int& x) 
    {
        while ((mvwinch(board_win, y = rand() % height, x = rand() % width)) != ' ');
    }

    void clear()
    {
        wclear(board_win);
        addBorder();
        wrefresh(board_win);
    }

    void refresh()
    {
        wrefresh(board_win);
    }
    
    int getStartRow() const
    {
        return start_row;
    }
    
    int getStartCol() const
    {
        return start_col;
    }

private:
    WINDOW *board_win;
    int height, width, start_row, start_col;

    void construct(int height, int width)
    {
        if (height <= 0 || width <= 0) {
            std::cerr << "Invalid board dimensions" << std::endl;
            return;
        }

        int yMax, xMax;
        getmaxyx(stdscr, yMax, xMax);
        this->height = height;
        this->width = width;
        start_row = (yMax / 2) - (height / 2);
        start_col = (xMax / 2) - (width / 2);


        if (height > yMax || width > xMax) {
            std::cerr << "Board dimensions are larger than terminal size" << std::endl;
            return;
        }

        // Center the board on the screen
        board_win = newwin(height, width, start_row, start_col);
        keypad(board_win, TRUE);
        if (board_win == nullptr) {
            std::cerr << "Error creating new window" << std::endl;
        } else {
            std::cout << "Board window created successfully" << std::endl;
            box(board_win, 0, 0);
            wrefresh(board_win);
        }
    }
};
