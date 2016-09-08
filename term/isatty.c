#include <unistd.h>	/* isatty */
int main (void)
{
    return isatty (STDOUT_FILENO);
}
