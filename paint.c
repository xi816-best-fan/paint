#include <ncurses.h>
#include <stdlib.h>

#define COLOR_BG 0
#define COLOR_FG 1

int main() {
    int ch;
    int x = 0, y = 0;

    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    start_color();
    init_pair(COLOR_FG, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_BG, COLOR_BLACK, COLOR_WHITE);

    while ((ch = getch()) != 'q') {
        switch (ch) {
            case KEY_UP:    y = y > 0 ? y - 1 : 0; break;
            case KEY_DOWN:  y = y < LINES - 1 ? y + 1 : LINES - 1; break;
            case KEY_LEFT:  x = x > 0 ? x - 1 : 0; break;
            case KEY_RIGHT: x = x < COLS - 1 ? x + 1 : COLS - 1; break;
            case ' ':
                if (mvinch(y, x) == ' ') {
                    attron(COLOR_PAIR(COLOR_FG));
                    mvaddch(y, x, '#');
                } else {
                    attron(COLOR_PAIR(COLOR_BG));
                    mvaddch(y, x, ' ');
                }
                break;
            case 'c':
                clear();
                break;
        }
        attron(A_REVERSE);
        mvaddch(y, x, ' ');
        attroff(A_REVERSE);
        refresh();
    }
    
    endwin();
    return 0;
}
