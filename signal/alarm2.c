#include <signal.h>	/* signal */
#include <stdio.h>	/* fprintf, printf */
#include <stdlib.h>	/* exit */
#include <unistd.h>	/* alarm */

void loop (void)
{
    int i;
    for (i = 0; i < 0xFFFFFF; i++)
        ;
}

void handler (int sig)
{
    printf ("hello\n");
    exit (0);
}

int main (void)
{
    signal (SIGALRM, handler);

    alarm (3);
    while (1) {
        loop ();
        fprintf (stderr, ".");
    }
}
