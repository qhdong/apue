#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>

void make_temp(char *template);

int main() {
    char template[] = "/tmp/myfileXXXXXX";
    make_temp(template);
}

void make_temp(char *template) {
    int fd;
    struct stat sbuf;

    if ((fd = mkstemp(template)) < 0) {
        perror("mkstemp()");
        return;
    }

    printf("temp name = %s\n", template);
    close(fd);

    if (stat(template, &sbuf) < 0) {
        if (errno == ENOENT) {
            printf("file dosen't exists\n");
        } else {
            perror("stat()");
            return;
        }
    } else {
        printf("file exists\n");
        unlink(template);
    }
}
