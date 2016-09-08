#include <stdio.h>	/* getchar, putchar */
#include <stdlib.h>	/* exit */
#include <termios.h>	/* tcgetattr, tcsetattr */
#include <unistd.h>	/* tcgetattr, tcsetattr */
int main (void)
{
    int c;
    struct termios new, old;
    tcgetattr (STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~(ICANON | ISIG);
    new.c_cc [VMIN]  = 1;
    new.c_cc [VTIME] = 0;
    tcsetattr (STDIN_FILENO, TCSANOW, &new);
    while ((c = getchar ()) != EOF) {
        if (c == 'q')
            exit (0);
        putchar (c);
    }
    tcsetattr (STDIN_FILENO, TCSANOW, &old);
}
