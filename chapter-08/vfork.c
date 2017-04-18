#include <unistd.h>
#include <stdio.h>

int globvar = 6;

int main(void) {
    int  var = 88;
    pid_t pid;

    printf("before vfork\n");

    if ((pid = vfork()) < 0) {
        perror("fork error");
        return -1;
    } else if (pid == 0) {
        ++globvar;
        ++var;
        _exit(0);
    }

    printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
}
