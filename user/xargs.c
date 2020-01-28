#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(int argc, char *argv[]){
	char *cmd[50];
	char buf[50][50];
	for(int i = 0; i < argc-1; i++)
		cmd[i] = argv[i+1];
	char bufread[512];
	int fd;
	while((fd = read(0, bufread, sizeof(bufread))) > 0){
		if(fd < 0){
			printf("xargs error!\n");
			exit();
		}
		int p = 0;
		int pp = 0;
		for(char *pointer = bufread;*pointer;pointer++){
			if(*pointer == ' ' || *pointer == '\n'){
				buf[p][pp] = '\0';
				p++;
				pp = 0;
			}else{
				buf[p][pp] = *pointer;
				pp++;
			}
		}
		buf[p][pp] = '\0';
		p++;
		for(int i=0;i<p;i++){
			cmd[i+argc-1] = buf[i];
		}
		if(fork()){
			wait();
		}else{
			exec(cmd[0], cmd);
		}
	}
	exit();
}
