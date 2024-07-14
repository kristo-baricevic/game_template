#pragma once
#include <ncurses.h>
#include "Board.hpp"
#include "Drawable.hpp"

class Game
{
public:
    Game(int height, int width)
    {
        board = Board(height, width);
        board.initialize();
        game_over = false;
    }

    void processInput()
    {
        chtype input = board.getInput();
    }

    void updateState()
    {
        board.add(Drawable(3, 3, '&'));
    }

    void redraw()
    {
        board.refresh();
    }

    bool isOver()
    {
        return game_over;
    }

private:
    Board board;
    bool game_over;
};
