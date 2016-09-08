#include <signal.h>	/* sigaddset, sigemptyset, signal, sigprocmask */
#include <stdio.h>	/* printf */
#define MAX 1000000
static volatile long long counter1 = 0, counter2 = 0;

void handler (int sig)
{
    counter1++;
    counter2++;
}

int main (void)
{
    long long i;
    sigset_t set, oset;

    signal (SIGINT, handler);
    sigemptyset (&set);
    sigaddset (&set, SIGINT);

    for (i = 0; i < MAX; i++) {
        sigprocmask (SIG_BLOCK, &set, &oset);
        counter1++;
        sigprocmask (SIG_SETMASK, &oset, NULL);
    }
    sigprocmask (SIG_BLOCK, &set, &oset);
    printf ("counter1 = %lld\n", counter1);
    printf ("counter2 = %lld\n", counter2);
    sigprocmask (SIG_SETMASK, &oset, NULL);
}
