/* fs/myls0.c */
#include <errno.h>      /* errno */
#include <sys/types.h>  /* closedir, opendir, readdir */
#include <stdio.h>      /* perror, printf */
#include <stdlib.h>     /* exit */
#include <dirent.h>     /* closedir, opendir, readdir */

int main(void) {
    DIR *dirp;
    struct dirent *p;

    if ((dirp = opendir(".")) == NULL) {
        perror("opendir");
        exit(1);
    }
    errno = 0;
    while ((p = readdir(dirp)) != NULL)
        printf("%s\n", p->d_name);
    if (errno != 0) { /* エラーがあると errno != 0 になる */
        perror("readdir");
        exit(1);
    }
    if (closedir(dirp) != 0) {
        perror("closedir");
        exit(1);
    }
    return 0;
}
