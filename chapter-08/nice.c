#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/time.h>

unsigned long long count;
struct timeval end;

void checktime(char *str) {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    if (tv.tv_sec >= end.tv_sec && tv.tv_usec >= end.tv_usec) {
        printf("%s count = %lld\n", str, count);
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    char *s;
    int nzero, ret;
    setbuf(stdout, NULL);
#if defined(NZERO)
    nzero = NZERO;
#elif defined(_SC_NZERO)
    nzero = sysconf(_SC_NZERO);
#else
#error NZERO undefined
#endif
    printf("NZERO = %d\n", nzero);
    int adj = 0;
    if (argc == 2) {
        adj = strtol(argv[1], NULL, 10);
    }
    gettimeofday(&end, NULL);
    end.tv_sec += 10;

    pid_t pid;
    if ((pid = fork()) < 0) {
        perror("fork()");
        return -1;
    } else if (pid == 0) {
        s = "child";
        printf("current nice value in child is %d, adjusting by %d\n",
                nice(0)+nzero, adj);
        errno = 0;
        if ((ret = nice(adj)) == -1 && errno != 0) {
            perror("nice()");
            return -2;
        }
        printf("current child nice value is %d\n", ret+nzero);
    } else {
        s = "parent";
        printf("current nice value in parent is %d\n", nice(0) + nzero);
    }

    while (1) {
        if (++count == 0) {
            printf("%s count wrap", s);
            return -1;
        }
        checktime(s);
    }
}
