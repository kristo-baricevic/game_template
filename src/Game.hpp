#pragma once
#include <ncurses.h>
#include "Board.hpp"
#include "Drawable.hpp"
#include "Dashboard.hpp"
#include "Empty.hpp"
#include "Snake.hpp"
#include "Character.hpp"
#include <ctime>
#include <cstdlib>

class Game
{
    Board board;
    Dashboard dashboard;
    Character *character;
    Snake snake;

public:
    Game(int height, int width)
    {
        board = Board(height, width);
        initialize(height, width);
    }

    ~Game()
    {
        delete character;
    }

    void initialize(int height, int width) 
    {
        character = nullptr;
        int sb_row = board.getStartRow() + height;
        int sb_col = board.getStartCol();
        dashboard = Dashboard(width, sb_row, sb_col);
        board.initialize();
        score = 0;
        dashboard.initialize(score);
        game_over = false;
        srand(time(nullptr));
        snake.setDirection(down);

        SnakePiece next = SnakePiece(1, 1);
        snake.addPiece(next);

        next = snake.nextHead();
        snake.addPiece(next);

        next = snake.nextHead();
        snake.addPiece(next);

        snake.setDirection(right);

        next = snake.nextHead();
        snake.addPiece(next);
    }

    void processInput()
    {
        chtype input = board.getInput();
        if (input == 'q') {
            game_over = true;
        }
        else if (input == 'w' || input == KEY_UP) {
            snake.setDirection(up);
        }
        else if (input == 's' || input == KEY_DOWN) {
            snake.setDirection(down);
        }
        else if (input == 'a' || input == KEY_LEFT) {
            snake.setDirection(left);
        }
        else if (input == 'd' || input == KEY_RIGHT) {
            snake.setDirection(right);
        }
    }

    void updateState()
    {
        int y, x;
        board.clear();

        // Add character if it doesn't exist
        if (character == nullptr) {
            board.getEmptyCoordinates(y, x);
            character = new Character(y, x);
        }

        // Add character to the board
        board.add(*character);

        // Move the snake
        SnakePiece next = snake.nextHead();

        // Check if snake head is at the character position
        if (next.getX() == character->getX() && next.getY() == character->getY()) {
            delete character; // Snake ate the character
            character = nullptr;
        } else {
            // Remove the tail if character is not eaten
            int emptyRow = snake.tail().getY();
            int emptyCol = snake.tail().getX();
            board.add(Empty(emptyRow, emptyCol));
            snake.removePiece();
        }

        snake.addPiece(next);

        // Add all snake pieces to the board
        std::queue<SnakePiece> pieces = snake.getPieces();
        while (!pieces.empty()) {
            board.add(pieces.front());
            pieces.pop();
        }

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
    bool game_over;
    int score;
};
