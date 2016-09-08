/* sub/mysub.c */
#include <stdlib.h>	/* atof, atoi, strtod, strtol */
#include <stdio.h>	/* fgets, fprintf, fputs, getc */
#include <limits.h>	/* strtol */
#include <string.h>	/* strchr, strcpy, strlen, strncpy */
#include "mysub.h"

static void discardline(FILE *);

enum {
    MAXLINE = 4096,
};

static void discardline(FILE *fp) {
    int c;

    while ((c = getc(fp)) != EOF)
        if (c == '\n') break;
}

int getint(char *prompt) {
    int d;
    char buf[MAXLINE];

    fputs(prompt, stderr);
    fgets(buf, MAXLINE, stdin);
    if (!strchr(buf, '\n')) discardline(stdin);
    d = (int)strtol(buf, (char**)NULL, 10);     /* または atoi(buf) */
    return d;
}

double getdouble(char *prompt) {
    double d;
    char buf[MAXLINE];

    fputs(prompt, stderr);
    fgets(buf, MAXLINE, stdin);
    if (!strchr(buf, '\n')) discardline(stdin);
    d = strtod(buf, (char**)NULL);              /* または atof(buf) */
    return d;
}

void getstr(char *prompt, char *s, int slen) {
    char *p, buf[MAXLINE];

    if (slen > MAXLINE)
        fprintf(stderr,
          "getstr: buffer length must be <= %d (%d specified);"
          " proceeding anyway\n", MAXLINE, slen);
    fputs(prompt, stderr);
    fgets(buf, MAXLINE, stdin);
    if ((p = strchr(buf, '\n')) == NULL)
        discardline(stdin);
    else
        *p = '\0';
    if (strlen(buf) < slen) {
        /* s に収まる */
        strcpy(s, buf);
    } else {
        /* 収まらないので後ろを切る */
        strncpy(s, buf, slen-1);
        s[slen-1] = '\0';
    }
}
