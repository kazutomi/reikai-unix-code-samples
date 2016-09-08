/* stdio/tinymining.c */
#include <assert.h>     /* assert */
#include <ctype.h>      /* isalpha */
#include <stdio.h>      /* fputs, getchar, printf, ungetc */
#include <stdlib.h>     /* exit */
#include <string.h>     /* strcmp, strlen */

enum {
    MYNAMELEN = 15,
};

char name[] = "Rie";
int myname, notmyname, junkchars;

void processword(void);

int main(void) {
    int c;

    assert(strlen(name) <= MYNAMELEN);
    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            if (ungetc(c, stdin) == EOF) {
                fputs("cannot ungetc\n", stderr);
                exit(1);
            }
            processword();
        } else
          junkchars++;
    }
    printf("my name %d, not my name %d, junk chars %d\n",
        myname, notmyname, junkchars);
    return 0;
}

void processword(void) {
    int c, i;
    char buf[MYNAMELEN+2];
    /*
     * strcmp() で違いが分かるように，語が長いときは
     * (MYNAMELEN+1) バイト読むようにする
     */

    i = 0;
    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            buf[i] = c;
            i++;
            if (i == sizeof(buf)-1) { /* 語が長いので残りを捨てる */
                while ((c = getchar()) != EOF) {
                    if (!isalpha(c)) {
                        if (ungetc(c, stdin) == EOF) {
                            fputs("cannot ungetc\n", stderr);
                            exit(1);
                        }
                        break;
                    }
                }
                goto wordgot;
            }
        } else {
            if (ungetc(c, stdin) == EOF) {
                fputs("cannot ungetc\n", stderr);
                exit(1);
            }
            goto wordgot;
        }
    }
wordgot:
    buf[i] = '\0';
    if (!strcmp(buf, name))
        myname++;
    else
        notmyname++;
}
