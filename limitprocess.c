#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>

int main()
{
   struct rlimit luv;
   luv.rlim_cur = 1;
   luv.rlim_max = 1;
   setrlimit (RLIMIT_NPROC, &luv);

   pid_t x = fork();
   printf("%d\n", x);

   pid_t y = fork();
   printf("%d\n", y); 
   return 0;
}
