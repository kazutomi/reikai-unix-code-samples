#include <sys/types.h>	/* read, write */
#include <sys/uio.h>	/* read, write */
#include <unistd.h>	/* close, pipe, read, write */
enum { SIZE = 1024 * 1024, };
int main (void)
{
    int fd [2], nbytes;
    char buf [SIZE], buf2 [SIZE];
    pipe (fd);
    write (fd [1], buf2, sizeof (buf2));
    nbytes = read (fd [0], buf, sizeof (buf));
    close (fd [0]);
    close (fd [1]);
}
