#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_t ntid;

void printids(const char *s) {
    pid_t pid = getpid();
    pthread_t tid = pthread_self();
    printf("%s pid %lu tid %lu (0x%lx)\n", s, pid, tid, tid);
}

void * thr_fn(void *arg) {
    printids("new thread: ");
    return ((void *)0);
}

int main() {
    int err = pthread_create(&ntid, NULL, thr_fn, NULL);
    if (err != 0) {
        perror("pthread_create");
        exit(-1);
    }
    
    printids("main thread:");
    sleep(1);
    return 0;
}
