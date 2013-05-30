// read_data.c

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

#define BUFSIZE 256
#define OUTPUT 256

int main(int argc, char* argv[]){
  int fd = open(argv[1], O_RDONLY, 0644);
  if(fd < 0){
    printf("file open failed");  
  }
  unsigned char buf[BUFSIZE];
  int offset = 0;
  while(1){
    int res = read(fd, buf, BUFSIZE);
    if(res == -1){
      printf("file read failed");
    }
    if(res == 0){
      break;
    }

    // read content
    int i;
    for(i = 0; i < res; i++){
      printf("%d %d\n", offset + i, buf[i] + 128);
    }

    if(res < BUFSIZE){
      break;
    }else{
      offset += BUFSIZE;
      if(offset >= OUTPUT){
	break;
      }
      continue;
    }
  }

  close(fd);

}
