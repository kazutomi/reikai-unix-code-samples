#include <signal.h>	/* sigaddset, sigemptyset, sigismember, sigprocmask */
#include <stdio.h>	/* printf */

int SIGINT_is_blocked (void)
{
    sigset_t old_sigset;
    sigprocmask (SIG_SETMASK, NULL, &old_sigset);
    return sigismember (&old_sigset, SIGINT);
}

int main (void)
{
    sigset_t sigset;
    sigemptyset (&sigset);
    sigaddset (&sigset, SIGINT);
    sigprocmask (SIG_BLOCK, &sigset, NULL);
    printf ("%d\n", SIGINT_is_blocked ());
    sigprocmask (SIG_UNBLOCK, &sigset, NULL);
    printf ("%d\n", SIGINT_is_blocked ());
}
