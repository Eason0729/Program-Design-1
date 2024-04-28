#include <stdbool.h>
#include "rust.h"

struct Node{
    void* val;
    __INTPTR_TYPE__ xor_;
};

struct Node* xor_new(void * val);
struct Node* xor_next(struct Node* previous,struct Node* current);
struct Node* xor_insert_front(struct Node* head,void* val);
struct Node* xor_insert_condition(struct Node* head,void* val,bool (*cmp)(void *,void *));
struct Node* xor_insert_mid(struct Node* previous,struct Node* current,void * val);
void debug_head(struct Node* head);
void * xor_remove(struct Node * previous,struct Node* current);
usize xor_count(struct Node* head);