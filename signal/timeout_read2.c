#include <assert.h>	/* assert */
#include <stdio.h>	/* fflush, perror, printf */
#include <sys/select.h>	/* FD_ISSET, FD_SET, FD_ZERO, select */
#include <sys/types.h>	/* read, write */
#include <sys/uio.h>	/* read, write */
#include <unistd.h>	/* read, write */

ssize_t timeout_read (int fd, void *buf, size_t count, int seconds)
{
    int ret;
    struct timeval timeout = {seconds, 0};
    fd_set rfd_set;

    FD_ZERO (&rfd_set);
    FD_SET  (STDIN_FILENO, &rfd_set);
    ret = select (STDIN_FILENO + 1, &rfd_set, NULL, NULL, &timeout);
    if (ret == -1) {
        perror ("select");
    } else if (ret == 0) {
        ret = -1;
    } else {
        assert (FD_ISSET (STDIN_FILENO, &rfd_set));
        ret = read (fd, buf, count);
    }
    return ret;
}

int main (void)
{
    char buf [1024];
    ssize_t ret;
    printf ("Please type your name: ");
    fflush (stdout);
    ret = timeout_read (STDIN_FILENO, buf, sizeof (buf), 3);
    if (ret == -1)
        printf ("timed out\n");
    else
        write (STDOUT_FILENO, buf, ret);
}
