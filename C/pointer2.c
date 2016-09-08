#include <termios.h>	/* tcgetattr */
#include <unistd.h>	/* tcgetattr */
int main (void)
{
    struct termios t;
    tcgetattr (STDIN_FILENO, &t);
}
