#include <ncurses.h>

void inicio();

int main(){
    initscr();
    noecho();
    curs_set(0);

    inicio();

    refresh();
    getch();
    endwin();
    return 0;
}

void inicio(){
    
    printw("Quiero agua\n");
    
}