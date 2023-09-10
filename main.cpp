#include <curses.h>
#include <ncurses.h>
#include "player.hpp"

#include <unistd.h> // for sleep
#include <string>

enum class State {
    MENU, PLAY, EXIT
};

State currentState = State::MENU;

// Global menu related variables
WINDOW* menu;
std::string choises[2] = {"PLAY", "EXIT"};
int choise, highlight = 0;

WINDOW* playWin;
Player* player;

void renderMenu() {
    for (int i = 0; i < 2; i++) {
        if (i == highlight)
            wattron(menu, A_REVERSE);
        mvwprintw(menu, 1 + i, 1, "%s", choises[i].c_str());
        wattroff(menu, A_REVERSE);
    }

    choise = wgetch(menu);
    switch (choise) {
        case KEY_UP:
            highlight--;
            break;
        case KEY_DOWN:
            highlight++;
            break;
        default:
            break;
    }

    if (choise == 10) { // Key Enter
        switch (highlight) {
            case 0:
                currentState = State::PLAY;
                break;
            case 1:
                currentState = State::EXIT;
                break;
            default:
                break;
        }
    }

    if (highlight < 0)
        highlight = 1;
    else if (highlight > 1)
        highlight = 0;

}

void renderGame() {
    do {
        player->display();
        wrefresh(playWin);
    } while (player->getMove() != int('q'));
    currentState = State::MENU;
}

int main() {

    initscr(); // ncurses init screen, setup memory

    cbreak(); // ctrl+c will exit ncurses (opposite of raw())
    //raw(); // raw ncurses input
    noecho(); // don't echo keypresses (ncurses)
    //nodelay(stdscr, TRUE);
    //scrollok(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    //move(row, column); // move ncurses cursor
    //mvprintw(row, column, text); // move cursor and print
    //clear(); // clears ncurses screen

    // Use for WINDOW* or specify stdscr for terminal info:
    //getyx(); // current cursor pos
    //getbegyx(); // top left corner pos
    //getmaxyx(); // height/width

    int termW, termH;
    getmaxyx(stdscr, termH, termW);
    printw("Terminal Width: %d Height: %d\n", termW, termH);

    // Setup menu window
    menu = newwin(6, termW - 12, termH - 8, 5);
    box(menu, 0, 0);
    refresh();
    wrefresh(menu);
    keypad(menu, true); // allows using arrow keys

    playWin = newwin(20, 50, (termH/2)-10, 10);
    box(playWin, 0, 0);
    refresh();
    //wrefresh(playWin);
    player = new Player(playWin, 1, 1, '@');

    bool running = true;
    while (running) {

        switch (currentState) {
            case State::MENU:
                renderMenu();
                break;
            case State::PLAY:
                renderGame();
                break;
            case State::EXIT:
                running = false;
                break;
        }
    }

    endwin(); // dealloce memory, end ncurses
    return 0;
}
