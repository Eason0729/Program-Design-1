// https://github.com/Seppel3210/rust-xor_-list

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "rust.h"

struct Node{
    void* val;
    __INTPTR_TYPE__ xor_;
};

// shortcut for xor_insert_mid(NULL,NULL,val)
struct Node* xor_new(void * val){
    struct Node* node=malloc(sizeof(struct Node));
    node->xor_=(__INTPTR_TYPE__)NULL;
    node->val=val;

    return node;
}

// find next node
struct Node* xor_next(struct Node* previous,struct Node* current){
    if(current==NULL) return NULL;
    return (struct Node*)((current->xor_)^((__INTPTR_TYPE__)previous));
}

// insert node at middle, return new node
struct Node* xor_insert_mid(struct Node* previous,struct Node* current,void * val){
    struct Node* node=malloc(sizeof(struct Node));
    if(previous!=NULL)previous->xor_^=((__INTPTR_TYPE__)current)^((__INTPTR_TYPE__)node);
    if(current!=NULL)current->xor_^=((__INTPTR_TYPE__)previous)^((__INTPTR_TYPE__)node);
    node->val=val;
    node->xor_=((__INTPTR_TYPE__)current)^((__INTPTR_TYPE__)previous);
    return node;
}

// insert randomly, return new node
struct Node* xor_insert_front(struct Node* head,void* val){
    struct Node* next=xor_next(NULL,head);
    return xor_insert_mid(head,next,val);
}
// insert after the element that make cmp return true, insert at front if not found, return new head
struct Node* xor_insert_condition(struct Node* head,void* val,bool (*cmp)(void *,void *)){
    if(head==NULL) return xor_new(val);

    struct Node* previous=NULL;
    struct Node* current=head;

    usize amount=0;
    while(current!=NULL){
        struct Node* next=xor_next(previous,current);
        if(cmp(val,current->val)){
            xor_insert_mid(current,next,val);
            return head;
        }
        previous=current;
        current=next;
    }

    return xor_insert_mid(NULL,head,val);
}

// remove current, return next
struct Node * xor_remove(struct Node * previous,struct Node* current){
    // printf("previous: %zu, current: %zu\n",previous,current);
    struct Node * next=xor_next(previous,current);
    if(previous!=NULL) previous->xor_^=(__INTPTR_TYPE__)current^(__INTPTR_TYPE__)next;
    if(next!=NULL) next->xor_^=(__INTPTR_TYPE__)current^(__INTPTR_TYPE__)previous;
    free(current);
    return next;
}

usize xor_count(struct Node* head){
    struct Node* previous=NULL;
    struct Node* current=head;

    usize amount=0;
    while(current!=NULL){
        struct Node* next=xor_next(previous,current);
        struct SizedSubmask* mask=current->val;
        amount++;

        previous=current;
        current=next;
    }
    return amount;
}

void debug_head(struct Node* head){
    struct Node* previous=NULL;
    struct Node* current=head;

    // printf("start of address:");
    while(current!=NULL){
        struct Node* next=xor_next(previous,current);
        struct SizedSubmask* mask=current->val;
        
        // printf("%zu ,",current);
        // fflush(stdout);

        previous=current;
        current=next;
    }
    // printf("\n");
}
// int test()
// {
//     usize my_item=10;

//     struct Node* first=xor_new(&my_item);
//     struct Node* second=xor_insert(NULL,first,&my_item);
//     struct Node* third=xor_insert(second,second,&my_item);

//     usize* my_item_ptr=xor_remove(first,second);

//     printf("%zu",*my_item_ptr);

//     return 0;
// }