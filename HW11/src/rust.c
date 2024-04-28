#include <stdlib.h>
#include <stdio.h>
#define u8 unsigned char
#define u16 unsigned short int
#define u32 unsigned int
#define u64 unsigned long int
#define i8 char
#define i16 short int
#define i32 int
#define i64 long int
#define usize size_t

void panic(char * msg){
    fprintf(stderr," [\x1B[31mERROR\x1B[0m ] %s\n",msg);
    *NULL;
}
void log_warn(char * msg){
    fprintf(stderr," [ \x1B[33mWARN\x1B[0m ] %s\n",msg);
}