#include "rust.h"
#include <stdio.h>
#include <stdlib.h>
unsigned long long int rdtsc_64bits()//64-bit
{
   unsigned long long int x;
   unsigned a, d;

   __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

   return ((unsigned long long)a) | (((unsigned long long)d) << 32);;
}


void output_csv(char * filename,u64 old){
   u64 new=rdtsc_64bits();
   
   FILE* file = fopen(filename , "a");

   fprintf(file, "%ld,",new-old);
   
   fflush(file);
   fclose(file);
}