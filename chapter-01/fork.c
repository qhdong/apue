#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 5000

static void sig_int(int);

int main() {
    char buf [MAXLINE];
    pid_t pid;
    int status;

    if (signal(SIGINT, sig_int) == SIG_ERR) {
        printf("signal error\n");
        return -1;
    }

    printf("%% ");
    while (fgets(buf, MAXLINE, stdin) != NULL) {
        if (buf[strlen(buf) - 1] == '\n') {
            buf[strlen(buf) - 1] = '\0';
        }
        if ((pid = fork()) < 0) {
            printf("frok error\n");
            return -1;
        } else if (pid == 0) {
            execlp(buf, buf, (char *)0);
            printf("could't execute %s\n", buf);
            exit(127);
        }

        if ((pid = waitpid(pid, &status, 0)) < 0) {
            printf("waitpid error\n");
            exit(1);
        }
        printf("%% ");
    }

    exit(0);
}

void sig_int(int signo) {
    printf("interrupt\n%% ");
}
