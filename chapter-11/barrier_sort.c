#include <pthread.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/time.h>

#define NTHR 1
#define NUMNUM  8000000L
#define TNUM    (NUMNUM / NTHR)
#define SECOND  1000000

long nums[NUMNUM];
long snums[NUMNUM];

pthread_barrier_t b;

#define heapsort qsort

int complong(const void *arg1, const void *arg2) {
    long l1 = *(long *)arg1;
    long l2 = *(long *)arg2;
    if (l1 == l2) return 0;
    else if (l1 < l2) return -1;
    else return 1;
}

double diff_time(struct timeval *start, struct timeval *end) {
    long long startusec = start->tv_sec * SECOND + start->tv_usec;
    long long endusec = end->tv_sec * SECOND + end->tv_usec;
    double elapsed = (double)(endusec - startusec) / 1000000.0;
    return elapsed;
}

void* thr_fn(void *arg) {
    long idx = (long)arg;
    struct timeval start, end;
    pthread_t tid = pthread_self();
    
    gettimeofday(&start, NULL);
    heapsort(&nums[idx], TNUM, sizeof(long), complong);
    gettimeofday(&end, NULL);

    printf("Thread [%4ld] completed. sort took %.4f seconds\n",
            tid, diff_time(&start, &end));

    pthread_barrier_wait(&b);

    printf("Thread [%4ld] wakeup\n", tid);

    return ((void*)0);
}

void merge() {
    long idx[NTHR];
    long minidx;
    for (long i = 0; i < NTHR; ++i) {
        idx[i] = i * TNUM;
    }
    for (long sidx = 0; sidx < NUMNUM; ++sidx) {
        long num = LONG_MAX;
        for (long i = 0; i < NTHR; ++i) {
            if ((idx[i] < (i+1) * TNUM) && (nums[idx[i]] < num)) {
                num = nums[idx[i]];
                minidx = i;
            }
        }
        snums[sidx] = nums[idx[minidx]];
        ++idx[minidx];
    }
}

int main() {
    unsigned long i;
    struct timeval start, end;
    long long startusec, endusec;
    double elapsed;
    int err;
    pthread_t tid;

    srandom(1);
    for (i = 0; i < NUMNUM; ++i) {
        nums[i] = random();
    }

    gettimeofday(&start, NULL);
    pthread_barrier_init(&b, NULL, NTHR + 1);
    for (i = 0; i < NTHR; ++i) {
        err = pthread_create(&tid, NULL, thr_fn, (void *)(i * TNUM));
        if (err != 0) {
            perror("pthread_create");
            exit(-1);
        }
    }

    pthread_barrier_wait(&b);
    merge();
    gettimeofday(&end, NULL);

    startusec = start.tv_sec * 1000000 + start.tv_usec;
    endusec = end.tv_sec * 1000000 + end.tv_usec;
    elapsed = (double)(endusec - startusec) / 1000000.0;
    printf("sort took %.4f seconds\n", elapsed);
    /* for (i = 0; i < NUMNUM; ++i) { */
    /*     printf("%ld\n", snums[i]); */
    /* } */
    exit(0);
}
