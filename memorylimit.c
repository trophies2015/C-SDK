<<<<<<< Updated upstream
#include <sys/resource.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, const char** argv) {
	struct rlimit lim;
	getrlimit(RLIMIT_DATA, &lim);
	lim.rlim_cur = 100;
	if (setrlimit(RLIMIT_AS, &lim)) {
      perror("setrlimit");
      return EXIT_FAILURE;
   }

	void* memory = malloc(2 * lim.rlim_cur);
	*(int*)memory = 3;
	if (memory != NULL) {
		puts("FAILURE");
		free(memory);
	}

	else {
		puts("SUCCESS");
	}

	return EXIT_SUCCESS;
}
=======
#include <sys/resource.h> 
 #include <sys/time.h> 
 #include <unistd.h> 
 #include<stdio.h> 
  
 int main () 
 {
   int a = 0;  
   struct rlimit rl;   
   rl.rlim_cur = 1; 
   rl.rlim_max = 1; 
   setrlimit (RLIMIT_CPU, &rl); 
   while (1){a++;}
   printf("%d\n", a); 
   return 0; 
 }
>>>>>>> Stashed changes
