#include <stdio.h>
#include <stdbool.h>
#include "linklist.h"
#include "hashmap.h"
#include "v1.h"
#include "v2.h"
#include "v3.h"
#include "rust.h"

int main()
{
    struct State state;
    state.head=NULL;

    input(&state);
    length_distribution(&state);
    segment(&state);
    prefix_insert(&state);
    prefix_delete(&state);
    search(&state);

    // FILE * table = fopen("routing_table.txt","r");
    // usize amount=0;
    // usize store[256];

    // for(usize i=0;i<256;i++)store[i]=0;

    // while(true){
    //     char buffer[20]={'\0'};
    //     fgets(buffer,20,table);
    //     if(*buffer=='\0') break;

    //     amount++;

    //     struct SizedSubmask mask;
    //     parse_submask(buffer,&mask);
    //     if(reduce_submask(&mask)) store[mask.mask.mask[3]]++;
    // }
    // printf("The total number of prefixes in the input file is : %zu.\n",amount);

    // fclose(table);

    // for(usize i=0;i<256;i++)printf("The number of prefixes in group %zu = %zu\n",i,store[i]);

    return 0;
}
