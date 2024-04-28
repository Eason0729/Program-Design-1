#include <stdbool.h>
#include "rust.h"
#define B 100

struct Entries{
    void* key;  
    void* val;
};
struct Entry{
    usize size;
    usize cap;  
    struct Entries* list;
};
struct HashMap{
    struct Entry entry[B];
    usize (*hasher)(void *);
    bool (*eq)(void *,void *);
};
void hash_new(struct HashMap* map,usize (*hasher)(void *), bool (*eq)(void *,void *));
void hash_insert(struct HashMap* map,void* key,void* val);
void* hash_get(struct HashMap* map,void* key);
void* hash_pop(struct HashMap* map,void* key);