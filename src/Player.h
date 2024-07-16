#ifndef PLAYER_H
#define PLAYER_H

#include <ncurses.h>
#include <vector>
#include <string>

// Function declaration
std::string loadAsciiArt(const std::string& filename);

class Player {
public:
    std::vector<std::string> playerFrames;
    std::vector<std::string> logoFrames;
    int current_frame;

    Player();
    void initPlayerPosition(WINDOW* game_wnd);
    void initLogo(WINDOW* game_wnd);
    void displayPlayer(WINDOW* game_wnd);
    void displayLogo(WINDOW* game_wnd);
    void clearPlayerPosition(WINDOW* game_wnd);
    void nextFrame();
};

#endif // PLAYER_H
