#include <stdio.h>	/* fprintf */
#include <sys/types.h>	/* fork */
#include <unistd.h>	/* fork, sleep */
int main (void)
{
    pid_t pid = fork ();
    int c = (pid == 0 ? '.' : '@');
    while (1) {
        fprintf (stderr, "%c", c);
        sleep (1);
    }
}
