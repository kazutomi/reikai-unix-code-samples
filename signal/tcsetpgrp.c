#include <stdio.h>	/* fprintf */
#include <sys/types.h>	/* fork, tcsetpgrp */
#include <unistd.h>	/* fork, setpgid, sleep, tcsetpgrp */
int main (void)
{
    pid_t pid = fork ();
    int c = (pid == 0 ? '.' : '@');
    if (pid != 0) {
        setpgid (pid, pid);
        tcsetpgrp (1, pid);
    }
    while (1) {
        fprintf (stderr, "%c", c);
        sleep (1);
    }
}
