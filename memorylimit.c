#include <sys/resource.h> 
 #include <sys/time.h> 
 #include <unistd.h> 
 #include<stdio.h> 
  
 int main () 
 { 
   struct rlimit rl;   
   rl.rlim_cur = 1; 
   rl.rlim_max = 1; 
   setrlimit (RLIMIT_CPU, &rl); 
   while (1){}
   return 0; 
 }
