#include <signal.h>	/* signal */
int main (void)
{
    signal (SIGINT, SIG_IGN);
    while (1);
}
