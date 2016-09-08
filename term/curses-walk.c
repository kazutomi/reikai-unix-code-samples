#include <curses.h>	/* cbreak, endwin, getch, initscr, move, mvaddch, mvinch, noecho, refresh */
static int y = 10, x = 10;

void print_player (void)
{
    mvaddch (y, x, '@');
    move (y, x); 
}

int main (void)
{
    char c, c2;
    initscr (); noecho (); cbreak (); 
    mvaddch (10, 20, '#');
    print_player ();

    while ((c = getch ()) != 'q') {
        int new_y = y, new_x = x;
        switch (c) {
        case 'h': new_x--; break;
        case 'j': new_y++; break;
        case 'k': new_y--; break;
        case 'l': new_x++; break;
        default:  continue;
        }
        
        c2 = mvinch (new_y, new_x) & A_CHARTEXT; 
        move (y, x);
        if (c2 == '#') continue;

        mvaddch (y, x, ' ');
        x = new_x; y = new_y;
        print_player ();
        refresh ();
    }
    endwin ();
}
