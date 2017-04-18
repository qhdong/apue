#include <unistd.h>
#include <stdio.h>

int globvar = 6;
char buf[] = "a write to stdout\n";

int main(void) {
    int  var = 88;
    pid_t pid;

    if (write(STDOUT_FILENO, buf, sizeof(buf) - 1) != sizeof(buf) - 1) {
        perror("write()");
        return -1;
    }
    printf("before fork\n");

    if ((pid = fork()) < 0) {
        perror("fork error");
        return -1;
    } else if (pid == 0) {
        ++globvar;
        ++var;
    } else {
        sleep(2);
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
}
