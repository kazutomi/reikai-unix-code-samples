/* proc/myvec.c */
#include <ctype.h>      /* isspace */

int strtovec(char *s, char **v, int max) {
    int i, skip;

    if (max < 1 || v == 0)
        skip = 1;
    else
        skip = 0;
    i = 0;
    for (;;) {
        if (!skip && i >= max - 1) {
            v[i] = 0;
            skip = 1;
        }
        /* 頭の空白を無視 */
        while (*s != '\0' && isspace(*s)) s++;
        if (*s == '\0') break;
        /* 空白でない文字が見つかった */
        if (!skip) v[i] = s;
        i++;
        /* その語の終わりを探す */
        while (*s != '\0' && !isspace(*s)) s++;
        if (*s == '\0') break;
        /* 空白が見つかった */
        *s = '\0';
        s++;
    }
    if (!skip)
        v[i] = 0;
    i++;
    return i;
}
