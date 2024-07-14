#include <ncurses.h>
#include "src/Board.hpp"
#include "src/Game.hpp"
#include "src/Drawable.hpp"


#define BOARD_DIM 28
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2

int main(int argc, char **argv)
{
    initscr();
    noecho();
    cbreak();
    refresh();
    curs_set(0);

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
