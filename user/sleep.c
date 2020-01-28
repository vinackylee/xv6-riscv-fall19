#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc <= 1){
    fprintf(2,"Usage: sleep time...\n");
    exit();
  }
  int time = atoi(argv[1]);
  sleep(time);
  exit();
}
