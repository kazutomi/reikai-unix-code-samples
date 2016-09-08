/* stdio/acctadd.c */
#include <stdio.h>      /* fclose, feof, fgets, fopen,
                                fprintf, fputs, putc, snprintf, sscanf */
#include <string.h>     /* strchr */
#include <time.h>       /* localtime_r, time */

#define ACCTBOOK "acctbook.txt"
enum {
    MAXLINELEN = 80,  /* 各項目について */
    BUFLEN = MAXLINELEN + 1,
};

int main(void) {
    FILE *fp;
    char buf[BUFLEN];
    char item[BUFLEN], value[BUFLEN];
    time_t unixtime;
    struct tm now;
    int year, month, day;
    double val;
    char *p;

    unixtime = time(NULL);
    localtime_r(&unixtime, &now);
    year = now.tm_year + 1900;
    month = now.tm_mon + 1; /* tm_mon = 0..11 */
    day = now.tm_mday;

    fp = fopen(ACCTBOOK, "a"); 
    for (;;) {
        fputs("item? ", stderr);
        fgets(item, sizeof(item), stdin); 
        if (feof(stdin)) break;
        if ((p = strchr(item, '\n')) != NULL) *p = '\0'; /* \n を切り落とす */
        fputs("value? ", stderr);
        fgets(value, sizeof(value), stdin); 
        if (sscanf(value, "%lf", &val) != 1) {
            fprintf(stderr, "value \"%s\" invalid; ignored\n", value);
            continue;
        }
        if (snprintf(buf, sizeof(buf), "%04d/%02d/%02d %.2f %s\n",
                 year, month, day, val, item) >= sizeof(buf)) {
             buf[sizeof(buf)-2] = '\n';
             fprintf(stderr, "Warning: entry too long; truncated to:\n%s", buf);
        }
        fputs(buf, fp); 
    }
    fclose(fp); 
    putc('\n', stderr);
    return 0;
}
