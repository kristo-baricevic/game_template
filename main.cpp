#include <ncurses.h>
#include "src/Board.hpp"
#include "src/Game.hpp"
#include "src/Drawable.hpp"

#define BOARD_DIM 20
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2

int main(int argc, char **argv)
{
    initscr();
    noecho();
    cbreak();
    refresh();

    Game game(BOARD_ROWS, BOARD_COLS);

    while (!game.isOver())
    {
        game.processInput();
        game.updateState();
        game.redraw();
    }

    getch();
    endwin();

    return 0;
}
