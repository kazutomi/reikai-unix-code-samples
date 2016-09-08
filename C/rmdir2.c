#include <stdio.h>	/* perror */
#include <stdlib.h>	/* exit, system */
#include <unistd.h>	/* rmdir */
#include <errno.h>	/* errno */
int main (void)
{
    if (rmdir ("foo") == -1) {
	int old_errno = errno;
	perror ("rmdir");
	if (old_errno == ENOTEMPTY) {
	    system ("ls foo");
	}
	exit (1);
    }
}
