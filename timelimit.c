#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <stdlib.h>


int main(){
  struct rlimit rl; 
  rl.rlim_cur = 1; 
  rl.rlim_max = 1; 
  
  setrlimit (RLIMIT_CPU, &rl); 
  int a=0; 
  while (1){a++;}
  return 0;
}
