#include <sys/types.h>	/* getpid, kill */
#include <stdio.h>	/* fprintf */
#include <signal.h>	/* kill, raise, signal */
#include <unistd.h>	/* getpid */
void handler (int sig)
{
    fprintf (stderr, "handler\n");
}

int main (void)
{
    signal (SIGINT, handler);
    kill (getpid (), SIGINT);
    raise (SIGINT);
}
