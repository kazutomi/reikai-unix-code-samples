#include <curses.h>	/* putp, setupterm, tigetstr, tparm */
#include <term.h>	/* putp, setupterm, tigetstr, tparm */
int main (void)
{
    char *p;
    setupterm (NULL, 0, NULL);
    p = tigetstr ("cup");
    p = tparm (p, 10, 20);
    putp (p);
}
