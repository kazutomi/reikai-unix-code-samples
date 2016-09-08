#include <sys/types.h>	/* open */
#include <stdio.h>	/* fprintf */
#include <stdlib.h>	/* exit */
#include <sys/stat.h>	/* open */
#include <fcntl.h>	/* open */
#include <unistd.h>	/* dup2, execvp */
int main (int argc, char *argv[])
{
    int fd;
    if (argc < 3) {
        fprintf (stderr, "%s filename command [arg...]\n", argv [0]);
        exit (1);
    }
    fd = open (argv [1], O_RDONLY);
    dup2 (fd, STDIN_FILENO);
    execvp (argv [2], &argv [2]);
}
