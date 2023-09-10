#pragma once

#include <ncurses.h>

class Player {
    public:
        Player(WINDOW* win, int y, int x, char c);

        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();
        void display();

        int getMove();

    private:
        int xLoc, yLoc, xMax, yMax;
        char symbol;
        WINDOW* currWin;
};
