#include <curses.h>	/* setupterm, tigetnum */
#include <stdio.h>	/* printf */
#include <term.h>	/* setupterm, tigetnum */
int main (void)
{
    setupterm (NULL, 0, NULL);
    printf ("lines = %d, cols = %d\n",
            tigetnum ("lines"), tigetnum ("cols"));
}
