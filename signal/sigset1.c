#include <signal.h>	/* sigaddset, sigemptyset */
int main (void)
{
    sigset_t sigset;
    sigemptyset (&sigset);
    sigaddset (&sigset, SIGINT);
    sigaddset (&sigset, SIGQUIT);
}
