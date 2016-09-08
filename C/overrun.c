#include <stdlib.h>	/* malloc */
#include <string.h>	/* strcpy, strlen */
int main (void)
{
    char *s2 = "hello";
    char *s1 = malloc (strlen (s2));
    strcpy (s1, s2);
}
