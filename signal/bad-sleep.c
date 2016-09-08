#include <signal.h>	/* signal */
#include <stdio.h>	/* printf */
#include <unistd.h>	/* alarm, pause */
void alarm_handler (int sig)
{
}

void my_sleep (int seconds)
{
    signal (SIGALRM, alarm_handler);
    alarm (seconds);
    pause ();
}

int main (void)
{
    printf ("hello(1)\n");
    my_sleep (3);
    printf ("hello(2)\n");
}
