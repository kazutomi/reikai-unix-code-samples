#include <signal.h>	/* sigaction, sigemptyset */
#include <stdio.h>	/* printf */
#include <stdlib.h>	/* exit */

void handler (int sig)
{
    printf ("hello\n");
    exit (1);
}

int main (void)
{
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags   = SA_RESTART;
    sigemptyset (&act.sa_mask);
    sigaction (SIGINT, &act, NULL);
    while (1);
}
