#include <signal.h>	/* sigaction, sigemptyset */
#include <stdio.h>	/* fprintf, printf */
#include <stdlib.h>	/* exit */
void handler (int sig, siginfo_t *info, void *q)
{
    fprintf (stderr, "faulting address = %p\n", info->si_addr);
    exit (1);
}

int main (void)
{
    struct sigaction act;
    act.sa_sigaction = handler;
    act.sa_flags = SA_SIGINFO;
    sigemptyset (&act.sa_mask);
    sigaction (SIGSEGV, &act, NULL);
    sigaction (SIGBUS,  &act, NULL);
    {
        int *p = (int*)0x123;
        printf ("%d\n", *p);
    }
}
