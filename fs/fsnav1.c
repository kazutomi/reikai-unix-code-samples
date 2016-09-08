/* fs/fsnav1.c */
#include <limits.h>     /* PATH_MAX */
#include <errno.h>      /* errno */
#include <sys/types.h>  /* closedir, mkdir, opendir, readdir */
#include <stdio.h>      /* fgets, fprintf, fputs, getchar,
                                perror, printf, putchar, setbuf */
#include <stdlib.h>     /* atexit, exit */
#include <string.h>     /* strchr */
#include <dirent.h>     /* closedir, opendir, readdir */
#include <termios.h>    /* tcgetattr, tcsetattr */
#include <unistd.h>     /* chdir, getcwd, tcgetattr, tcsetattr, unlink */

void restoreterm(void);
void showlist(void);
void showcwd(void);
void goup(void);
void godown(void);
void delfile(void);

struct termios termsave, termcur;
void restoreterm(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &termsave); 
}

void showlist(void) {
    DIR *dp;
    struct dirent *dep;

    if ((dp = opendir(".")) == NULL) {
        fprintf(stderr, "cannot open directory\n");
        return;
    }
    errno = 0;
    while ((dep = readdir(dp)) != NULL)
        printf("%s ", dep->d_name);
    if (errno == 0)
        putchar('\n');
    else
        perror("\nreaddir");
    closedir(dp);
}

void showcwd(void) {
    char buf[PATH_MAX+1];

    getcwd(buf, sizeof(buf)); 
    printf("%s\n", buf);
}

void goup(void) {
    chdir(".."); 
}

void godown(void) {
    char buf[PATH_MAX+1], *p;

    tcsetattr(STDIN_FILENO, TCSANOW, &termsave); 
    fputs("directory? ", stderr);
    fgets(buf, sizeof(buf), stdin); 
    if ((p = strchr(buf, '\n')) != NULL)
        *p = '\0';
    if (chdir(buf) != 0)
        perror("chdir");
    tcsetattr(STDIN_FILENO, TCSANOW, &termcur); 
}

void delfile(void) {
    char buf[PATH_MAX+1], *p;

    tcsetattr(STDIN_FILENO, TCSANOW, &termsave); 
    fputs("file to remove? ", stderr); 
    fgets(buf, sizeof(buf), stdin); 
    if ((p = strchr(buf, '\n')) != NULL)
	*p = '\0';
    if (unlink(buf) != 0)
	perror("unlink");
    tcsetattr(STDIN_FILENO, TCSANOW, &termcur); 
}

int main(void) {
    int c;

    tcgetattr(STDIN_FILENO, &termsave); 
    termcur = termsave;
    if (atexit(restoreterm) != 0) {
        perror("atexit");
        exit(1);
    }
    termcur.c_lflag &= ~(ICANON | ECHO);
    termcur.c_cc[VMIN] = 1;
    termcur.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &termcur); 
    setbuf(stdin, NULL);

    for (;;) {
        c = getchar();
        switch (c) {
            case 'l': showlist(); break;
            case 'u': goup(); showcwd(); break;
            case 'd': godown(); showcwd(); break;
            case '?': showcwd(); break;
            case 'r': delfile(); break;
            case 'q': goto finish;
            default: fprintf(stderr, "unknown command '%c'\n", c); break;
        }
    }
finish:
    exit(0);
}
