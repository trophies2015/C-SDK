#include <sys/resource.h> 
#include <sys/time.h> 
#include <unistd.h> 
#include<stdio.h> 
#include <stdlib.h>  
int main () 
 { 
   struct rlimit rl;   
   rl.rlim_cur = 100; 
   rl.rlim_max = 100; 
   setrlimit (RLIMIT_AS, &rl); 
   getrlimit (RLIMIT_AS, &rl); 
   printf("%lld\n", rl.rlim_cur);
   char * p; 
   p = (char *) malloc (1024);
   if (p == NULL) printf("%s\n", "FAILED"); 
   else printf("%s\n", "SUCCESS"); 
   return 0; 
 }
