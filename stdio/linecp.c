/* stdio/linecp.c */
#include <stdio.h>      /* fclose, fgets, fopen, fputs, perror */
#include <stdlib.h>     /* exit */
enum {
    LINELEN = 1024,
};

int main(int argc, char *argv[]) {
    FILE *ifp, *ofp;
    char buf[LINELEN];

    if (argc != 3) {
        fputs("usage: linecp <infile> <outfile>\n", stderr);
        exit(1);
    }
    ifp = fopen(argv[1], "r"); 
    ofp = fopen(argv[2], "w"); 
    while (fgets(buf, sizeof(buf), ifp) != NULL) { 
        if (fputs(buf, ofp) == EOF)
            perror("fputs");
    }
    fclose(ofp); 
    fclose(ifp); 
    return 0;
}
