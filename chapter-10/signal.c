#include <pwd.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <stdio.h>

static void my_alarm(int signo) {
    struct passwd *rootptr;

    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL) {
        perror("getpwnam");
    }
    alarm(1);
}

int main() {
    struct passwd *ptr;
    signal(SIGALRM, my_alarm);
    alarm(1);
    while (1) {
        if ((ptr = getpwnam("aaron")) == NULL) {
            perror("getpwnam");
        }
        if (strcmp(ptr->pw_name, "aaron") != 0) {
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
        }
    }
}
