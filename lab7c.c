#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMELTS 16384

int prime(int n)
{
  int ret=1, i;
  for(i=2; i<=(int) sqrt(n) && ret; i++)
    ret=n % i;
  return ret;
}
int main()
{
  int data[NUMELTS];
  int fd[2];
  int pid, inData, counter=0;

  if (pipe(fd) == -1)
    return -1;

  srand(time(NULL));
  for(int i=0; i<NUMELTS; i++)
    data[i]=(int) (((double) rand() / (double) RAND_MAX) * 10000);

  if ((pid = fork())) {
    for (int i=0; i<NUMELTS/2; i++)
      if (prime(data[i]))
        counter++;
    read(fd[0], &inData, sizeof(inData));
    close(fd[1]);
    printf("Total number of primes in given range is %d", inData+counter);
  }
  else {
    for (int i=NUMELTS/2; i<NUMELTS; i++)
      if (prime(data[i]))
        counter++;
    write(fd[1], &counter, sizeof(counter));
    close(fd[0]);
    return 0;
  }
  return 0;
}
