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
