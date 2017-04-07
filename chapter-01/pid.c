#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("hello world from process %ld\n", (long)getpid());
    printf("my father is %ld\n", (long)getppid());
}
