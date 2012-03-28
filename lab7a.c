#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#define PARENT_DELAY 1
#define CHILD_DELAY 2

int main()
{
  pid_t pid;
  int i, j, k, status;
  k=15;
  if ((pid=fork()))
    {
      printf("Process ID of parent's parent: %d\n", getppid());
      printf("Process ID of child: %d\n", pid);
      for(i=0; i<10; i++)
        {
          printf("Parent: i=%d k=%d\n", i, k);
          k++;
          // Delay
          sleep(PARENT_DELAY);
        }
      if (wait(&status) == -1)
        return -1;
    }
  else
    {
      for(i=10; i<50; i++)
        {
          printf("Child: i=%d, k=%d\n", i, k);
          sleep(CHILD_DELAY);
        }
    }
}
