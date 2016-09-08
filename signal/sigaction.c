#include <signal.h>	/* sigaction, sigemptyset */
#include <stdio.h>	/* fprintf */
#include <unistd.h>	/* sleep */
void handler (int sig)
{
    fprintf (stderr, "@");
}

int main (void)
{
    struct sigaction act;
    act.sa_handler = handler;
    act.sa_flags   = 0;
    sigemptyset (&act.sa_mask);
    sigaction (SIGINT, &act, NULL);
    while (1) {
        sleep (1);
        fprintf (stderr, ".");
    }
}
