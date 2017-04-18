#include <stdio.h>
#include <unistd.h>

int main()
{
    char *ptr;
    size_t size;
    if (chdir("/var/log") < 0) {
        perror("chdir");
        return -1;
    }
    ptr = getcwd(NULL, 10);
    printf("cwd = %s\n", ptr);
    exit(0);
}
