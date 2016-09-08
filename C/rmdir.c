#include <stdio.h>	/* perror */
#include <stdlib.h>	/* exit */
#include <unistd.h>	/* rmdir */
int main (void)
{
    if (rmdir ("foo") == -1) {
	perror ("rmdir");
	exit (1);
    }
}
