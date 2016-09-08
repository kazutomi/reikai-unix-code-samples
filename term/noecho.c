#include <stdio.h>	/* getchar, putchar */
#include <termios.h>	/* tcgetattr, tcsetattr */
#include <unistd.h>	/* tcgetattr, tcsetattr */
int main (void)
{
    int c;
    struct termios new, old;
    tcgetattr (STDIN_FILENO, &old);
    new = old;
    new.c_lflag &= ~ECHO;
    tcsetattr (STDIN_FILENO, TCSANOW, &new);
    while ((c = getchar ()) != EOF) {
        putchar (c);
    }
    tcsetattr (STDIN_FILENO, TCSANOW, &old);
}
