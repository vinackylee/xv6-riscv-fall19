#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

  int fd_parent[2];
  int fd_child[2];
  char buf[10];
  pipe(fd_parent);
  pipe(fd_child);
  if(fork()==0){
    read(fd_parent[0],buf,4);
    printf("%d: received %s\n",getpid(),buf);
    write(fd_child[1],"pong",4);
  }else{
    write(fd_parent[1],"ping",4);
    read(fd_child[0],buf,4);
    printf("%d: received %s\n",getpid(),buf);

  }
  exit();
}
