
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
   struct rlimit luv;
   luv.rlim_cur = 1;
   luv.rlim_cur = 1;
   setrlimit (RLIMIT_NPROC, &luv);
   int g; 
	for (g=0; g<3; g++) assert(fork() < 0);
   return 0;
}



