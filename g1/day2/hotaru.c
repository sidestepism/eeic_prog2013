#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>

#define LENGTH 1
#define BPS 8000
#define MAX_SIZE 256

int main(int argc, char* argv[]){
  if(argc != 3){
    printf("usage: $ signwave [amptitude] [frequency]");
    return 1;
  }

  float A = atof(argv[1]);
  float f = atof(argv[2]);

  int melody[] = {
    7, 0, 0, 0, 4, 2, 0, 2,
    4, 0, 0, 4, 7, 9, 9, 9,
    9, 7, 4, 4, 0, 2, 0, 2,
    4, 0, 9, 9, 7, 0, 0, 0
  };

  int melody_len = 32;
  int i = 0,
    length = LENGTH * BPS;

  float fb = f * 2 * M_PI / BPS;
  float ab = A * MAX_SIZE / 2;
  
  int n;
  for(n = 0; n < melody_len; n++){
    unsigned char buf[length];
    fb = 440 * pow(2, melody[n]/12) * M_PI / BPS;
  
    for(i = 0; i < length; i++){
    buf[i] = (unsigned char)floor(ab * sin(i * fb));
    // printf("%d\n", buf[i]);
    }
    write(1, buf, length);
  }

  // printf("A: %f, f: %f, fb: %f, ab: %f", A, f, fb, ab);
  // int res = write(1, buf, length * melody_len);
  return 0;
}
