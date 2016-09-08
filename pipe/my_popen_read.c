#include <sys/types.h>	/* fork, read, write */
#include <sys/uio.h>	/* read, write */
#include <unistd.h>	/* close, dup2, execlp, fork, pipe, read, write */

int my_popen_read (const char *command)
{
    int fd [2];
    pid_t pid;

    pipe (fd);
    if ((pid = fork ()) == 0) {
        dup2 (fd [1], 1);
        close (fd [0]); close (fd [1]);
        execlp (command, command, (char *)NULL);
    }
    close (fd [1]);
    return fd [0];
}

int main (void)
{
    int fd, nbytes;
    char buf [1024];

    fd = my_popen_read ("ls");
    while (1) {
        nbytes = read (fd, buf, sizeof (buf));
        if (nbytes <= 0) break;
        write (STDOUT_FILENO, buf, nbytes);
    }
    close (fd);
}
