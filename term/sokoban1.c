#include <curses.h>	/* endwin, getch, initscr, move, printw, refresh */
#include <stdio.h>	/* fclose, fgets, fopen, fprintf, sscanf */
#include <stdlib.h>	/* exit */
enum { MAX_CHARS = 1024 };
static int y, x, num;
static void load_map (char *filename)
{
    int i, ret;
    char buf [MAX_CHARS];
    FILE *fp = fopen (filename, "r");
    fgets (buf, sizeof (buf), fp);
    ret = sscanf (buf, "y=%d, x=%d, num=%d", &y, &x, &num);
    if (ret != 3) {
        fprintf (stderr, "bad data file format\n");
        exit (1);
    }
    for (i = 0; i < LINES; i++) {
        if (fgets (buf, sizeof (buf), fp) == NULL)
            break;
        move   (i, 0);
        printw ("%s", buf);
    }
    fclose (fp);
}

int main (void)
{
    initscr ();
    load_map ("sokoban.map");
    refresh ();
    getch ();
    endwin ();
}
