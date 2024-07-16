#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include "Player.h"

// Function definition
std::string loadAsciiArt(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return "";
    }

    std::string line, art;
    while (std::getline(file, line)) {
        art += line + "\n";
    }

    file.close();
    return art;
}

// Player class methods
Player::Player() : current_frame(0) {}

void Player::initPlayerPosition(WINDOW* game_wnd) {
    // Load player frames from text files
    playerFrames.push_back(loadAsciiArt("clam1.txt"));
    playerFrames.push_back(loadAsciiArt("clam2.txt"));
    playerFrames.push_back(loadAsciiArt("clam3.txt"));

    if (playerFrames.empty()) {
        std::cerr << "No frames loaded." << std::endl;
        return;
    }

    displayPlayer(game_wnd);
}

void Player::initLogo(WINDOW* game_wnd) {
    // Load logo frames from text files
    logoFrames.push_back(loadAsciiArt("logo.txt"));
    logoFrames.push_back(loadAsciiArt("logo.txt"));

    if (logoFrames.empty()) {
        std::cerr << "No frames loaded." << std::endl;
        return;
    }

    displayLogo(game_wnd);
}

void Player::displayPlayer(WINDOW* game_wnd) {
    clearPlayerPosition(game_wnd);
    std::string& current_frame_str = playerFrames[current_frame];

    int y = 1; // Starting y position
    int x = 1; // Starting x position

    // Print each line of the frame at the appropriate position
    std::stringstream ss(current_frame_str);
    std::string line;
    int line_offset = 0;
    while (std::getline(ss, line, '\n')) {
        mvwprintw(game_wnd, y + line_offset, x, "%s", line.c_str());
        line_offset++;
    }

    wrefresh(game_wnd);
}

void Player::displayLogo(WINDOW* game_wnd) {
    clearPlayerPosition(game_wnd);
    std::string& current_frame_str = logoFrames[current_frame];

    int y = 1; // Starting y position
    int x = 1; // Starting x position

    // Print each line of the frame at the appropriate position
    std::stringstream ss(current_frame_str);
    std::string line;
    int line_offset = 0;
    while (std::getline(ss, line, '\n')) {
        mvwprintw(game_wnd, y + line_offset, x, "%s", line.c_str());
        line_offset++;
    }

    wrefresh(game_wnd);
}

void Player::clearPlayerPosition(WINDOW* game_wnd) {
    int y = 1; // Starting y position
    int x = 1; // Starting x position

    // Clear each line of the frame at the appropriate position
    for (int i = 0; i < 35; ++i) { // Adjust the number of lines to match your ASCII art height
        mvwprintw(game_wnd, y + i, x, "                                                                             "); // Adjust the width to match your ASCII art width
    }

    wrefresh(game_wnd);
}

void Player::nextFrame() {
    current_frame = (current_frame + 1) % playerFrames.size();
}
