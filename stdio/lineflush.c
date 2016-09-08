/* stdio/lineflush.c */
#include <stdio.h>      /* printf, scanf */

int main(void) {
    int age;

    printf("How old are you? ");
    scanf("%d", &age);
    printf("You are %d years old\n", age);
    return 0;
}
