#include <stdio.h>

#define MAXLINE 1024

int main() {
    char line[MAXLINE];
    FILE *fp;

    if ((fp = tmpfile()) == NULL) {
        perror("tmpfile()");
        return -1;
    }

    fputs("hello, world", fp);
    rewind(fp);
    fgets(line, MAXLINE, fp);
    fputs(line, stdout);
    return 0;
}
