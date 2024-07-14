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
    bool game_over;
    int score;

public:
    Game(int height, int width)
    : board(height, width),
      dashboard(width, board.getStartRow() + height, board.getStartCol()),
      character(nullptr), snake(), game_over(false), score(0)
    {
        initialize(height, width);
    }

    ~Game()
    {
        delete character;
    }

    void initialize(int height, int width) 
    {
        if (character != nullptr) {
            delete character;
            character = nullptr;
        }
        dashboard.initialize(score);
        board.initialize();
        srand(time(nullptr));
        
        // Reset snake
        snake = Snake();
        snake.setDirection(Direction::right);

        // Start with a single piece
        SnakePiece initialPiece(1, 1);
        board.add(initialPiece);
        snake.addPiece(initialPiece);

        createCharacter();
    }

    void handleNextPiece(SnakePiece next)
    {
        if (!board.isWithinBounds(next.getY(), next.getX())) {
            game_over = true;
            return;
        }

        if (character != nullptr && next.getX() == character->getX() && next.getY() == character->getY()) {
            destroyCharacter();
        } else if (!snake.getPieces().empty()) {
            int emptyRow = snake.tail().getY();
            int emptyCol = snake.tail().getX();
            board.add(Empty(emptyRow, emptyCol));
            snake.removePiece();
        }

        board.add(next);
        snake.addPiece(next);
    }

     void createCharacter() 
    {
        int y, x;
        board.getEmptyCoordinates(y, x);
        if (board.isWithinBounds(y, x)) {
            character = new Character(y, x);
            board.add(*character);
        }
    }

    void destroyCharacter()
    {
        if (character != nullptr) {
            board.add(Empty(character->getY(), character->getX()));  // Replace character with empty space
            delete character;
            character = nullptr;
        }
    }

    void updateState()
    {
        if (!game_over) {
            handleNextPiece(snake.nextHead());

            if (character == nullptr) {
                createCharacter();
            }

            score += 1;
            dashboard.updateScore(score);
        }
    }

    void processInput()
    {
        chtype input = board.getInput();
        if (input == 'q') {
            game_over = true;
        }
        else if (input == 'w' || input == KEY_UP) {
            snake.setDirection(Direction::up);
        }
        else if (input == 's' || input == KEY_DOWN) {
            snake.setDirection(Direction::down);
        }
        else if (input == 'a' || input == KEY_LEFT) {
            snake.setDirection(Direction::left);
        }
        else if (input == 'd' || input == KEY_RIGHT) {
            snake.setDirection(Direction::right);
        }
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
};
