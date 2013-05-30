// mk_data.c
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(){
  int i = 0;
  int fd = open("./mk_data", O_TRUNC | O_CREAT | O_WRONLY, 0644);
  assert(fd);
  if(fd < 0){
    printf("file open failed\n");
    return 1;
  }
  char data[256];
  for(i = 0; i < 256; i++){
    data[i] = i;
  }
  int res = write(fd, data, 256);
  if(res == -1){
    printf("file write failed\n");  
  }
  printf("%d", res);
  close(fd);
  return 0;
}
