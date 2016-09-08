#include <curses.h>	/* attron, endwin, getch, getnstr, initscr, move, noecho, printw, refresh */
int main (void)
{
    char buf [1024];
    initscr ();
    noecho ();
    getnstr (buf, sizeof (buf));
    move (2, 10);
    attron (A_REVERSE);
    printw ("input = %s\n", buf);
    refresh ();
    getch ();
    endwin ();
}
