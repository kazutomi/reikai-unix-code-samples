#include <stdio.h>	/* perror */
#include <stdlib.h>	/* exit */
#include <sys/types.h>	/* read, write */
#include <sys/uio.h>	/* read, write */
#include <unistd.h>	/* close, pipe, read, write */
int main (void)
{
    int fd [2], nbytes;
    char buf [1024];
    if (pipe (fd) == -1) {
        perror ("pipe");
        exit (1);
    }
    write (fd [1], "Hello\n", 6);
    nbytes = read (fd [0], buf, sizeof (buf));
    write (STDOUT_FILENO, buf, nbytes);
    close (fd [0]); close (fd [1]);
}
