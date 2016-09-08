#include <signal.h>	/* signal */
#include <stdio.h>	/* printf */
#include <stdlib.h>	/* exit */
void handler (int sig)
{
    printf ("hello\n");
    exit (1);
}

int main (void)
{
    signal (SIGINT, handler);
    while (1);
}
