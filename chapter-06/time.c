#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    time_t t;
    time(&t);

    struct tm *tmp;
    tmp = localtime(&t);

    char buf1[64];

    if (strftime(buf1, 64, "time and date: %r, %a %b %d, %Y", tmp) == 0) {
        printf("buffer length 64 is too small\n");
    } else {
        printf("%s\n", buf1);
    }
}

