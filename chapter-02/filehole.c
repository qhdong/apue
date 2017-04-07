#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main() {
    int fd;
    if ((fd = creat("file.hole", FILE_MODE)) == -1) {
        printf("creat error");
        return -1;
    }

    if (write(fd, buf1, 10) != 10) {
        printf("buf1 write error");
        return -2;
    }

    if (lseek(fd, 16384, SEEK_SET) == -1) {
        printf("seek error");
        return -3;
    }

    if (write(fd, buf2, 10) != 10) {
        printf("buf2 write error");
        return -4;
    }

    return 0;

}
