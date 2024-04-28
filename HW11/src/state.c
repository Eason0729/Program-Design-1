#include <stdio.h>
#include <stdlib.h>
#include "rust.h"
#include "linklist.h"
#include "hashmap.h"
#define D 8

union Submask
{
    u8 mask[4];
    u32 raw;
};

struct SizedSubmask
{
    union Submask mask;
    usize len;
};

usize parse_number(char** cstr_ptr){
    usize tmp=0;
    while((**cstr_ptr<='9')&&(**cstr_ptr>='0')){
        tmp=tmp*10+(usize)(**cstr_ptr-'0');
        (*cstr_ptr)++;
    }
    return tmp;
}

usize display_submask(struct SizedSubmask *mask){
    printf("%hd.%hd.%hd.%hd/%zu",mask->mask.mask[3],mask->mask.mask[2],mask->mask.mask[1],mask->mask.mask[0],mask->len);
}

usize display_ip(struct SizedSubmask *mask){
    printf("%hd.%hd.%hd.%hd",mask->mask.mask[3],mask->mask.mask[2],mask->mask.mask[1],mask->mask.mask[0]);
}

void parse_submask(char* cstr, struct SizedSubmask *mask){
    for (usize i=0;i<4;i++){
        mask->mask.mask[3-i]=(u8)parse_number(&cstr);
        cstr++;
    }

    if(*cstr<'0'||*cstr>'9'){
        usize i=0;
        for (i=0;i<4;i++)
            if(mask->mask.mask[3-i]==0)break;
        mask->len=i*8;
    }else mask->len=parse_number(&cstr);
}

void parse_ip(char* cstr, union Submask *mask){
    for (usize i=0;i<4;i++){
        mask->mask[3-i]=(u8)parse_number(&cstr);
        cstr++;
    }
}
struct SizedSubmask* scale(union Submask* mask){
    struct SizedSubmask* result=malloc(sizeof(struct SizedSubmask));

    result->mask.raw=(((mask->raw)>>(32-D))<<(32-D));
    result->len=D;
    return result;
}

struct SizedSubmask* clone_submask(struct SizedSubmask *mask){
    struct SizedSubmask *new=malloc(sizeof(struct SizedSubmask));
    new->len=mask->len;
    new->mask.raw=mask->mask.raw;
    return new;
}

bool reduce_submask(struct SizedSubmask* source){
    if(source->len<D)return false;
    

    u32 mask=source->mask.raw;
    source->len=D;
    source->mask.raw=((mask>>(32-D))<<(32-D));

    return true;
}

struct State{
    struct Node* head;
    struct HashMap hashmap;
};

// int test()
// {
//     char *example = "192.168.1.1/24";
//     struct SizedSubmask mask;
//     parse_submask(example, &mask);

//     printf("CIDR: %u.%u.%u.%u/%u\n", mask.mask.mask[3], mask.mask.mask[2], mask.mask.mask[1], mask.mask.mask[0],mask.len);

//     return 0;
// }