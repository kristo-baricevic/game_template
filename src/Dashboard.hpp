#pragma once
#include <ncurses.h>

class Dashboard
{
    WINDOW *dashboard_win;

public:
    Dashboard() {}

    Dashboard(int width, int y, int x)
    {
        dashboard_win = newwin(10, width, y, x); // Make it 3 lines high for better visibility
        box(dashboard_win, 0, 0);
        wrefresh(dashboard_win);
    }

    void initialize(int initial_score)
    {
        clear();
        mvwprintw(dashboard_win, 1, 1, "SCORE: ");
        updateScore(initial_score);
        refresh();
    }

    void updateScore(int score)
    {
        int max_x = getmaxx(dashboard_win);
        mvwprintw(dashboard_win, 1, max_x - 10, "%d", score); // Use %d for integers
    }

    void clear()
    {
        wclear(dashboard_win);
        box(dashboard_win, 0, 0);
    }

    void refresh()
    {
        wrefresh(dashboard_win);
    }
};
