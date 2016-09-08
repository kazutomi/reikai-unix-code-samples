#include <curses.h>	/* addch, cbreak, endwin, getch, inch, initscr, move, noecho, printw, refresh */
#include <stdio.h>	/* fclose, fgets, fopen, sscanf */
#define DEFAULT_DAT_FILENAME "sokoban.map"

enum { WALL = '#', ROCK = '\'', PIT  = '^', SELF = '@', SPACE = ' ', };

enum {
    KB_UP  = 'k', KB_DOWN  = 'j', KB_RIGHT  = 'l', KB_LEFT  = 'h',
    KB_UP2 = 'K', KB_DOWN2 = 'J', KB_RIGHT2 = 'L', KB_LEFT2 = 'H',
    KB_QUIT = 'q', KB_REFRESH = 'r',
};

static int y, x;
static int  num;

static void load_map (char *filename)
{
    int i;
    char buf [1024];
    FILE *fp = fopen (filename, "r");
    fgets (buf, sizeof (buf), fp);
    sscanf (buf, "y = %d, x = %d, num = %d", &y, &x, &num);
    for (i = 0; i < LINES; i++) {
        if (fgets (buf, sizeof (buf), fp) == NULL)
            break;
        move (i, 0);
        printw ("%s", buf);
    }
    fclose (fp);
}

static void sokoban_init (char *filename)
{
    initscr (); noecho (); cbreak ();
    load_map (filename);
    move (y, x);
}

static void sokoban_end (void)
{
    if (num == 0) {
        move (1, 1);
        printw ("You won! Congratulations!!");
        move (2, 1);
        printw ("Type any key to end: ");
        getch ();
    }

    clear (); refresh (); endwin ();
}

static void step (int dy, int dx)
{
    chtype c;
    int new_y = y + dy, new_x = x + dx;
    move (new_y, new_x);
    c = inch () & A_CHARTEXT;
    if (c == WALL || c == PIT) return;
    if (c == ROCK) {
        move (new_y + dy, new_x + dx);
        c = inch () & A_CHARTEXT;
        if (!(c == SPACE || c == PIT)) return;
        if (c == SPACE) {
            addch (ROCK);
        } else if (c == PIT) {
            addch (SPACE);
            num--;
            move (LINES - 1, 0);
            printw ("%d item(s) left", num);
        }
    }
    move (y, x); addch (SPACE);
    y += dy; x += dx;
    move (y, x); addch (SELF);
}

static void run (int dy, int dx)
{
    while (1) {
        int prev_y = y, prev_x = x;
        step (dy, dx);
        if (y == prev_y && x == prev_x)
            break;
    }
}

static void sokoban_main_loop (void)
{
    int c;
    refresh ();

    while (num != 0 && (c = getch()) != KB_QUIT) {
        switch (c) {
        case KB_LEFT:    step (0, -1); break;
        case KB_LEFT2:   run  (0, -1); break;
        case KB_DOWN:    step (+1, 0); break;
        case KB_DOWN2:   run  (+1, 0); break;
        case KB_UP:      step (-1, 0); break;
        case KB_UP2:     run  (-1, 0); break;
        case KB_RIGHT:   step (0, +1); break;
        case KB_RIGHT2:  run  (0, +1); break;
        case KB_REFRESH: refresh ();   break;
        default:                       break;
        }
        move (y, x); refresh ();
    }
}

int main (int argc, char *argv [])
{
    char *filename = DEFAULT_DAT_FILENAME;
    if (argc >= 2)
        filename = argv [1];
    sokoban_init (filename);
    sokoban_main_loop ();
    sokoban_end  ();
}
