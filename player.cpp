#include "player.hpp"

Player::Player(WINDOW* win, int y, int x, char c)
    : currWin(win), yLoc(y), xLoc(x), symbol(c) {

    getmaxyx(win, yMax, xMax);
    keypad(win, true);
}

void Player::moveUp() {
    mvwaddch(currWin, yLoc, xLoc, ' '); // Clear previous player pos
    yLoc--;
    if (yLoc < 1)
        yLoc = 1;
}

void Player::moveDown() {
    mvwaddch(currWin, yLoc, xLoc, ' '); // Clear previous player pos
    yLoc++;
    if (yLoc > yMax - 2)
        yLoc = yMax - 2;
}

void Player::moveRight() {
    mvwaddch(currWin, yLoc, xLoc, ' '); // Clear previous player pos
    xLoc++;
    if (xLoc > xMax - 2)
        xLoc = xMax - 2;
}

void Player::moveLeft() {
    mvwaddch(currWin, yLoc, xLoc, ' '); // Clear previous player pos
    xLoc--;
    if (xLoc < 1)
        xLoc = 1;
}

void Player::display() {
    mvwaddch(currWin, yLoc, xLoc, symbol);
    //mvwprintw(currWin, xLoc, xLoc, "%c", symbol);
}

int Player::getMove() {
    int choise = wgetch(currWin);
    switch (choise) {
        case KEY_UP:
            moveUp();
            break;
        case KEY_DOWN:
            moveDown();
            break;
        case KEY_LEFT:
            moveLeft();
            break;
        case KEY_RIGHT:
            moveRight();
            break;
        default:
            break;
    }

    return choise;
}
