#include <stdio.h>	/* fprintf */
#include <sys/types.h>	/* fork, getpid */
#include <unistd.h>	/* fork, getpid, setpgid, sleep */
int main (void)
{
    pid_t pid = fork ();
    int c = (pid == 0 ?  '.' : '@');
    if (pid == 0) {
        setpgid (getpid (), getpid ());
    }
    while (1) {
        fprintf (stderr, "%c", c);
        sleep (1);
    }
}
