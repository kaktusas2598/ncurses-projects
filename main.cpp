#include <ncurses.h>

#include <unistd.h> // for sleep

int kbhit(void)
{
    int ch = getch();

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

int main() {

    initscr(); // ncurses init screen, setup memory

    cbreak(); // ctrl+c will exit ncurses (opposite of raw())
    //raw(); // raw ncurses input
    noecho(); // don't echo keypresses (ncurses)
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    //move(row, column); // move ncurses cursor
    //mvprintw(row, column, text); // move cursor and print
    //clear(); // clears ncurses screen

    // Use for WINDOW* or specify stdscr for terminal info:
    //getyx(); // current cursor pos
    //getbegyx(); // top left corner pos
    //getmaxyx(); // height/width

    //keypad(win, true); // ??

    //int c = wgetch(win); // get char from window

    int termW, termH;
    getmaxyx(stdscr, termH, termW);
    printw("Terminal Width: %d Height: %d\n", termW, termH);

    int height = 5, width = 20;
    int start_y = 5, start_x = 10;
    WINDOW* win = newwin(height, width, start_y, start_x); // create ncurses window
    refresh();

    box(win, '|', '-'); // put a border around window
    //wborder(win, ...); // for complete border control
    mvwprintw(win, 1, 2, "Window text!");
    wrefresh(win);

    bool running = true;
    while (running)
    {
        attron(COLOR_PAIR(1));
        printw("Waiting...\n");
        attroff(COLOR_PAIR(1));
        if (kbhit()) {
            printw("Key pressed!\n");
            char pressedKey = getch();
            //if (pressedKey == '1')
            //else if (pressedKey == '2')
            if (pressedKey == 'q')
                running = false;
            refresh();
        } else {
            refresh();
            sleep(1);
        }

    }

    endwin(); // dealloce memory, end ncurses
    return 0;
}
