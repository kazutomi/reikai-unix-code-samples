#include <signal.h>	/* signal */
#include <stdio.h>	/* printf */
#define MAX 1000000000
static volatile long long counter1 = 0, counter2 = 0;
void handler (int sig)
{
    counter1++;
    counter2++;
}

int main (void)
{
    long long i;
    signal (SIGINT, handler);
    for (i = 0; i < MAX; i++) {
        counter1++;
    }
    printf ("counter1 = %lld\n", counter1);
    printf ("counter2 = %lld\n", counter2);
}
