#include <stdio.h>

int main() {
    char name[6] = "hello";

    printf("name addr       : 0x%08X\n", name);
    printf("&name[0] addr   : 0x%08X\n", &name[0]);
    printf("&name addr      : 0x%08X\n", &name);
    printf("name+1 addr     : 0x%08X\n", name + 1);
    printf("&name+1 addr    : 0x%08X\n", &name + 1);
    printf("name size       : %u\n", sizeof(name));

    printf("\n");

    char *pname = "hello";

    printf("pname addr      : 0x%08X\n", pname);
    printf("&pname[0] addr  : 0x%08X\n", &pname[0]);
    printf("&pname addr     : 0x%08X\n", &pname);
    printf("pname+1 addr    : 0x%08X\n", pname + 1);
    printf("&pname+1 addr   : 0x%08X\n", &pname + 1);
    printf("pname size      : %u\n", sizeof(pname));
}
