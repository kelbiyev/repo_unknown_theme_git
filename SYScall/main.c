#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main () {
    char buffer[100];
    int bytesRead;
    bytesRead = syscall(SYS_read , 0 , buffer , sizeof(buffer) - 1);
    if(bytesRead == 1) {
        perror("Syscall failed");
        exit(1);
    }
    buffer[bytesRead] = '\0';
    printf("you typed: %s\n" , buffer);
    return 0;
}