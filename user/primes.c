#include "kernel/types.h"
#include "user/user.h"

void redirect(int port, int fd[]){
    close(port);
    dup(fd[port]);
    close(fd[0]);
    close(fd[1]);
}

void compute(int n){
    int buf;
    while(read(0, &buf, sizeof(buf))){
        if(buf % n != 0){
            write(1, &buf, sizeof(buf));
        }
    }
    close(1);
}

void newpro(){
    int fd[2];
    int buf;

    if(read(0, &buf, sizeof(buf))){
        printf("prime %d\n", buf);
        pipe(fd);
        if(fork()){
            redirect(1, fd);
            compute(buf);
        }else{
            redirect(0,fd);
            newpro();
        }
    }
}

int main(){
    int fd[2];
    pipe(fd);

    if(fork()){
        for(int i=2;i<35;i++){
            write(fd[1], &i, sizeof(i));
        }
        close(fd[1]);
        close(fd[0]);
    }else{
        redirect(0,fd);
        newpro();
    }
    exit();
}
