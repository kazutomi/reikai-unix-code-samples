#include <signal.h>	/* signal */
#include <stdio.h>	/* fprintf */
#include <unistd.h>	/* pause */
void handler (int sig)
{
    fprintf (stderr, "handler\n");
}
int main (void)
{
    signal (SIGINT, handler);
    pause ();
    fprintf (stderr, "hello, world\n");
}
