#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void charatatime(const char *str);

int main() {
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork()");
        return -1;
    } else if (pid == 0) {
        charatatime("output from child\n");
    } else {
        charatatime("output from parent\n");
    }
    exit(0);
}

void charatatime(const char *str) {
    setbuf(stdout, NULL);
    while (*str) {
        putc(*str++, stdout);
    }
}
