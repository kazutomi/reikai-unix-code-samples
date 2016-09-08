#include <stdio.h>	/* perror */
#include <errno.h>	/* errno */
int main (void)
{
    errno = ENOENT;
    perror ("test");
}
