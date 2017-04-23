#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>

char *env_init[] = {"USER=unknown", "PATH=/tmp", NULL};

int main(void) {
    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork()");
        return -1;
    } else if (pid == 0) {
        if (execle("/home/aaron/Playground/C/apue/chapter-08/echoall.out",
                    "echoall", "myarg1", "MY ARG2", (char *)0, env_init) < 0) {
            perror("execle");
            return -2;
        }
        if (waitpid(pid, NULL, 0) < 0) {
            perror("wait error");
        }
    }

    return 0;
}
