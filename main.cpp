#include <ncurses.h>
#include "src/Board.hpp"
#include "src/Game.hpp"
#include "src/Drawable.hpp"
#include "src/Player.h"
#include <unistd.h>


#define BOARD_DIM 28
#define BOARD_ROWS BOARD_DIM
#define BOARD_COLS BOARD_DIM * 2

int main(int argc, char **argv)
{
    initscr();
    noecho();
    cbreak();
    refresh();
    // curs_set(0);
    curs_set(FALSE);

    // Game game(BOARD_ROWS, BOARD_COLS);
    WINDOW* game_wnd = newwin(40, 100, 0, 0);
    WINDOW* dash = newwin(20, 100, 40, 0);

    Player player;
    player.initPlayerPosition(game_wnd);
    player.initLogo(dash);
        player.displayLogo(dash);

    while (true) {
        player.displayPlayer(game_wnd);

        player.nextFrame();

        usleep(500000); // Sleep for 0.5 seconds
    }

    // while (!game.isOver())
    // {
    //     game.processInput();
    //     game.updateState();
    //     game.redraw();
    // }

    getch();
    endwin();

    return 0;
}


