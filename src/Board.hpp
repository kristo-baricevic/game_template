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

private:
    WINDOW *board_win;

    void construct(int height, int width)
    {
        if (height <= 0 || width <= 0) {
            std::cerr << "Invalid board dimensions" << std::endl;
            return;
        }

        int yMax, xMax;
        getmaxyx(stdscr, yMax, xMax);

        std::cout << "Terminal size: " << yMax << "x" << xMax << std::endl;
        std::cout << "Board size: " << height << "x" << width << std::endl;

        if (height > yMax || width > xMax) {
            std::cerr << "Board dimensions are larger than terminal size" << std::endl;
            return;
        }

        // Center the board on the screen
        board_win = newwin(height, width, (yMax / 2) - (height / 2), (xMax / 2) - (width / 2));
        if (board_win == nullptr) {
            std::cerr << "Error creating new window" << std::endl;
        } else {
            std::cout << "Board window created successfully" << std::endl;
            box(board_win, 0, 0);
            wrefresh(board_win);
        }
    }
};
