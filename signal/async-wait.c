#include <signal.h>	/* signal */
#include <stdio.h>	/* fprintf, perror, printf */
#include <stdlib.h>	/* exit */
#include <sys/types.h>	/* fork, waitpid */
#include <sys/wait.h>	/* waitpid */
#include <unistd.h>	/* execlp, fork, sleep */
#include <errno.h>	/* errno */

void handler (int sig)
{
    pid_t pid;
    while ((pid = waitpid (-1, NULL, WNOHANG)) != 0) {
        if (pid == -1) {
            if (errno == ECHILD) break;
            if (errno == EINTR)  continue;
            perror ("waitpid");
            exit (1);
        }
        printf ("handler: pid = %d\n", pid);
    }
}

int main (void)
{
    pid_t pid = fork ();
    signal (SIGCHLD, handler);
    if (pid == 0) {
        execlp ("cat", "cat", (char *)0);
    }
    while (1) {
        fprintf (stderr, ".");
        sleep (1);
    }
}
