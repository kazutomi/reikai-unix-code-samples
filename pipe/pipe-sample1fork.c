#include <sys/types.h>	/* fork, read, wait, write */
#include <sys/uio.h>	/* read, write */
#include <sys/wait.h>	/* wait */
#include <unistd.h>	/* close, fork, pipe, read, write */

int main (void)
{
    int n, fd [2];
    char buf [1024];
    pid_t pid;

    pipe (fd);
    if ((pid = fork ()) == 0) {
        close (fd [1]);
        n = read (fd [0], buf, sizeof (buf));
        write (1, buf, n);
        close (fd [0]);
    } else {
        close (fd [0]);
        write (fd [1], "Hello\n", 6);
        close (fd [1]);
        wait (NULL);
    }
}
