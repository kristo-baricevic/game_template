#pragma once
#include <ncurses.h>
#include "Board.hpp"
#include "Drawable.hpp"
#include "Dashboard.hpp"

class Game
{
public:
    Game(int height, int width)
    {
        board = Board(height, width);
        int sb_row = board.getStartRow() + height;
        int sb_col = board.getStartCol();
        dashboard = Dashboard(width, sb_row, sb_col);
        board.initialize();
        score = 0;
        dashboard.initialize(score);
        game_over = false;
    }

    void processInput()
    {
        chtype input = board.getInput();
        if (input == 'q') {
            game_over = true;
        }
    }

    void updateState()
    {
        board.clear();
        board.add(Drawable(3, 3, '&'));
        score += 1;
        dashboard.updateScore(score);
    }

    void redraw()
    {
        board.refresh();
        dashboard.refresh();
    }

    bool isOver()
    {
        return game_over;
    }

private:
    Board board;
    Dashboard dashboard;
    bool game_over;
    int score;
};
