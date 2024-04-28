#define clock_start usize freq=0;\
    u64 begin=rdtsc_64bits();
#define clock_end u64 end=rdtsc_64bits(); 

// #define record_start u64 r_begin=rdtsc_64bits();
// #define record_end(x) output_csv(x,r_begin);

#define record_start ;
#define record_end(x) ;

unsigned long long int rdtsc_64bits();
void output_csv(char * filename,unsigned long long int old);