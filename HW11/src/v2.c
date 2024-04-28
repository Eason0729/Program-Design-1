#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "linklist.h"
#include "hashmap.h"
#include "state.h"
#define D 8

// assume there is no prefix like this 192.0.0.0/1, this is a strange prefix,
// because 192.0.0.0 has first two bit set, but is has submask smaller than two

// determine whether two SizedSubmask are equal
bool eq(void* a,void* b){
    struct SizedSubmask* mask_a=a;
    struct SizedSubmask* mask_b=b;
    return mask_a->mask.raw==mask_b->mask.raw;
}

// if a>b, return true
bool cmp(void* a,void* b){
    struct SizedSubmask* mask_a=a;
    struct SizedSubmask* mask_b=b;
    return mask_a->mask.raw>mask_b->mask.raw;// for debug
}

// hasher for SizedSubmask
usize hasher(void* a){
    struct SizedSubmask* mask=a;
    return mask->mask.raw;
}

// printf usize as binary
void print_binary(usize j){
    for(size_t i=1;i<=D;i++){
        printf("%s",(0==(j&(1<<(D-i))))?"0":"1");
    }
}

// std::collections::HashMap<SizedSubmask,XorLinklist<SizeSubmask>>

// segment state->head into HashMap<SizedSubmask,XorLinklist<SizeSubmask>>
// 
// where the key is reduced(only retain first D bit)
void segment(struct State* state){
    state->hashmap=malloc(sizeof(struct HashMap));
    hash_new(state->hashmap,hasher,eq);

    struct Node* current=state->head;
    
    state->head=NULL;

    // iterator all element in the LinkList
    while (current!=NULL){
        struct SizedSubmask* mask= current->val;
        struct SizedSubmask* ip=clone_submask(mask);
        current=xor_remove(NULL,current);
        if(reduce_submask(mask)){
            struct Node* ll=hash_pop(state->hashmap,mask);
            struct Node* new=xor_insert_mid(NULL,ll,ip);
            hash_insert(state->hashmap,mask,new);
        }else{
            state->head=xor_insert_condition(state->head,ip,cmp);
            free(mask);
        }
    }

    // list all ips
    for(usize i=0;i<(1<<D);i++){
        struct SizedSubmask mask;
        mask.len=D;
        mask.mask.raw=i<<(32-D);

        // struct Node* head=hash_get(state->hashmap,&mask);
        // printf("The number of prefixes in group %zu = %zu\n",i,xor_count(head));
        printf("| ");
        print_binary(i);
        printf(" |");

        struct Node* current=hash_get(state->hashmap,&mask);
        struct Node* previous=NULL;

        while(current!=NULL){
            struct Node* next=xor_next(previous,current);

            printf(" ---> | ");
            display_ip(current->val);
            printf(" |");

            previous=current;
            current=next;
        }
        printf("\n");
    }

    {
        printf("--------special group--------\n");

        struct Node* current=state->head;
        struct Node* previous=NULL;

        while(current!=NULL){
            struct Node* next=xor_next(previous,current);

            display_ip(current->val);
            printf("\n");
            
            previous=current;
            current=next;
        }
        
        printf("-----------------------------\n");
    }

}