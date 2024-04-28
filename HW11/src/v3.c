#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "linklist.h"
#include "state.h"
#include "hashmap.h"
#include "clock.h"

// check if two SizedSubmask are equal
bool eq_v3(void* a,void* b){
    struct SizedSubmask* mask_a=a;
    struct SizedSubmask* mask_b=b;
    return mask_a->mask.raw==mask_b->mask.raw;
}

// check if target(Submask) is within val(SizedSubmask)
bool eq_v3_subset(void* val,void* target){
    struct SizedSubmask* mask=val;
    union Submask* ip=target;
    usize r_bit=32-(mask->len);
    return (mask->mask.raw<<r_bit)==(ip->raw<<r_bit);
}

// remove match element, return new head
struct Node* xor_remove_match(struct Node* head,void* target,bool (*eq)(void *,void *)){
    struct Node* previous=NULL;
    struct Node* current=head;
    struct Node* next=NULL;
    while(current!=NULL){
        if(eq(current->val,target)){
            free(current->val);
            next=xor_remove(previous,current);
            break;
        }
        struct Node* next=xor_next(previous,current);
        
        previous=current;
        current=next;
    }
    if(previous==NULL) return next;
    else return head;
}

// iterate all element in target, return false if for
// every element eq(element[i], target) return false, return true otherwise
bool xor_contain(struct Node* current,void* target,bool (*eq)(void *,void *)){
    struct Node* previous=NULL;
    while(current!=NULL){
        struct Node* next=xor_next(previous,current);
        if(eq(current->val,target))return true;
        previous=current;
        current=next;
    }
    return false;
}

void prefix_insert(struct State* state){
    FILE * table = fopen("inserted_prefixes.txt","r");

    clock_start

    while(true){
        char buffer[20]={'\0'};
        fgets(buffer,20,table);
        if(*buffer=='\0') break;

        struct SizedSubmask* mask=malloc(sizeof(struct SizedSubmask));
        parse_submask(buffer,mask);
        struct SizedSubmask* ip=clone_submask(mask);

        record_start

        if(reduce_submask(mask)){
            struct Node* ll=hash_pop(state->hashmap,mask);
            
            struct Node* new=xor_insert_mid(NULL,ll,ip);
            hash_insert(state->hashmap,mask,new);
        }else state->head=xor_insert_mid(NULL,state->head,ip);
        
        record_end("prefix_insert.csv")

        freq++;
    }

    clock_end
}

void prefix_delete(struct State* state){
    FILE * table = fopen("deleted_prefixes.txt","r");

    clock_start

    while(true){
        char buffer[20]={'\0'};
        fgets(buffer,20,table);
        if(*buffer=='\0') break;

        struct SizedSubmask* mask=malloc(sizeof(struct SizedSubmask));
        parse_submask(buffer,mask);
        struct SizedSubmask* ip=clone_submask(mask);

        record_start

        if(reduce_submask(mask)){
            struct Node* ll=hash_pop(state->hashmap,mask);
            if(ll==NULL){
                log_warn("not found");
            }
            struct Node* new_head=xor_remove_match(ll,ip,eq_v3);

            if(new_head!=NULL)hash_insert(state->hashmap,mask,new_head);
        }else{
            struct Node* ll=state->head;
            struct Node* new_head=xor_remove_match(ll,ip,eq_v3);
            if(new_head!=NULL) state->head=new_head;
        }
        freq++;

        record_end("prefix_delete.csv")

        free(ip);
    }

    clock_end
}

void search(struct State* state){
    FILE * table = fopen("trace_file.txt","r");

    clock_start

    while(true){
        char buffer[20]={'\0'};
        fgets(buffer,20,table);
        if(*buffer=='\0') break;

        union Submask ip;
        parse_ip(buffer,&ip);
        struct SizedSubmask* mask=scale(&ip);

        freq++;

        record_start

        struct Node* ll=hash_get(state->hashmap,mask);
        
        if (xor_contain(ll,&ip,eq_v3_subset)||xor_contain(state->head,&ip,eq_v3_subset))
            printf("successful\n");
        else printf("failed\n");
            
        record_end("search.csv")

        free(mask);
    }

    clock_end
}