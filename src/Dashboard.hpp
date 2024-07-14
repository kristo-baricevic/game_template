#pragma once
#include <ncurses.h>

class Dashboard
{
    WINDOW *dashboard_win;

public:
    Dashboard()
    {
    }

    Dashboard(int width, int y, int x)
    {
        dashboard_win = newwin(1, width, y, x);
    }

    void initialize(int initial_score)
    {
        clear();
        mvwprintw(dashboard_win, 0, 0, "SCORE");
        updateScore(initial_score);
        refresh();
    }

    void updateScore(int score)
    {
        int max_x = getmaxx(dashboard_win);
        mvwprintw(dashboard_win, 0, max_x - 10, "%11d", score); // Use %d for integers
    }

    void clear()
    {
        wclear(dashboard_win);
    }

    void refresh()
    {
        wrefresh(dashboard_win);
    }
};
