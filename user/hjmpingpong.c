// pingpong
#include "kernel/types.h"
#include "user/user.h"

int main() {
    int p[2]; int p1[2];
    char buf[] = {'a'};
    // int pid;
    int count = 0;;

    if(pipe(p) < 0 || pipe(p1) < 0){
        printf("pipe failed\n");
        exit(1);
    }

    int ret = fork();
    if ( ret < 0){
        fprintf(2, "fork sys call fails\n");
        exit(1);
    }

    if (ret == 0) {
        // pid = getpid();
        close(p[0]);
        close(p1[1]);
        while(1){
        read(p1[0], buf, 1);
        // printf("%d: received ping\n", pid);
        write(p[1], buf, 1);
        count++;
        printf("count %d\n", count);
        }
        exit(0);
    } else {
        // pid = getpid();
        close(p1[0]);
        close(p[1]);
        while(1){
        write(p1[1], buf, 1);
        read(p[0], buf, 1);
        // printf("%d: received pong\n",pid);
        }
        exit(0);
    }
}
