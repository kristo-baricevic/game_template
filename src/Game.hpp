#pragma once
#include <ncurses.h>
#include "Board.hpp"
#include "Drawable.hpp"
#include "Dashboard.hpp"
#include "Empty.hpp"
#include "Character.hpp"
#include <time.h>
#include <stdlib.h>


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
        srand(time(NULL));
    }

    ~Game()
    {
        delete character;
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
        int y, x;
        board.getEmptyCoordinates(y, x);
        board.clear();
        if (character != NULL) 
            board.add(Empty(character->getY(), character->getX()));
 
        character = new Character(y, x);
        board.add(*character);
        board.add(Drawable(3, 4, '@'));

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
    Character *character;
    bool game_over;
    int score;
};
