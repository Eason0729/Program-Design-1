#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "linklist.h"
#include "state.h"

void input(struct State* state){
    FILE * table = fopen("routing_table.txt","r");
    usize amount=0;

    while(true){
        char buffer[20]={'\0'};
        fgets(buffer,20,table);
        if(*buffer=='\0') break;

        amount++;

        struct SizedSubmask* mask=malloc(sizeof(struct SizedSubmask));
        parse_submask(buffer,mask);

        state->head=xor_insert_mid(NULL,state->head,mask);
    }
    printf("The total number of prefixes in the input file is : %zu.\n",amount);
}

void length_distribution(struct State* state){
    usize lens[33]={0};

    struct Node* previous=NULL;
    struct Node* current=state->head;

    while(current!=NULL){
        struct Node* next=xor_next(previous,current);
        struct SizedSubmask* mask=current->val;
        lens[mask->len]++;

        previous=current;
        current=next;
    }

    for(usize i=0;i<=32;i++)
        printf("the number of prefixes with prefix length %zu = %zu.\n",i,lens[i]);
}