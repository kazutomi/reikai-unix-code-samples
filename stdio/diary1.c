/* stdio/diary1.c */
#include <stdio.h>      /* clearerr, fclose, feof, ferror,
                                    fgets, fopen, fputs, perror */
#include <stdlib.h>     /* exit */
#include "mysub.h"

enum {
    MAXLINE = 1024,
};

void writediary(void);
void readdiary(void);

int main(void) {
    int cmd;

    for (;;) {
        cmd = getint("1=write, 2=read, 3=end: ");
        switch (cmd) {
            case 1:
                writediary();
                break;
            case 2:
                readdiary();
                break;
            case 3:
                return 0;
            default:
                fputs("unknown command\n", stderr);
                break;
        }
    }
}

void writediary(void) {
    FILE *fp;
    char date[MAXLINE], s[MAXLINE];

    getstr("date (MMDD): ", date, sizeof(date));
    fp = fopen(date, "w"); 
    while (fgets(s, sizeof(s), stdin) != NULL) {
        fputs(s, fp); 
    }
    if (feof(stdin)) { /* EOFか? */
        clearerr(stdin);
    } else {           /* エラー */
        perror("fgets");
        exit(1);
    }
    fclose(fp); 
}

void readdiary(void) {
    FILE *fp;
    char date[MAXLINE], s[MAXLINE];

    getstr("date (MMDD): ", date, sizeof(date));
    fp = fopen(date, "r"); 
    while (fgets(s, sizeof(s), fp) != NULL) {
        fputs(s, stdout);
    }
    if (ferror(fp)) { /* エラー? */
        perror("fgets");
        exit(1);
    }
    fclose(fp); 
}
