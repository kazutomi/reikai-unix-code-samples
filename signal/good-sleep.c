#include <signal.h>	/* sigaddset, sigemptyset, signal, sigprocmask */
#include <stdio.h>	/* printf */
#include <unistd.h>	/* alarm */
void alarm_handler (int sig)
{
}

void my_sleep2 (int seconds)
{
    sigset_t new_sigset, old_sigset;
    sigemptyset (&new_sigset);
    sigaddset (&new_sigset, SIGALRM);
    signal (SIGALRM, alarm_handler);
    sigprocmask (SIG_BLOCK, &new_sigset, &old_sigset);
    alarm (seconds);
    sigsuspend (&old_sigset);
    sigprocmask (SIG_SETMASK, &old_sigset, NULL);
}

int main (void)
{
    printf ("hello(1)\n");
    my_sleep2 (3);
    printf ("hello(2)\n");
}
