#include <stdbool.h>
#include <stdio.h>
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

//.please return '1' in clang, because only exactly '1' are guarantee to be true,
// value other than '0' and '1' in bool can cause UB.

// initialize hashmap
void hash_new(struct HashMap* map,usize (*hasher)(void *), bool (*eq)(void *,void *)){
    map->eq=eq;
    map->hasher=hasher;
    for(usize i=0;i<B;i++){
        map->entry[i].cap=1;
        map->entry[i].list=malloc(sizeof(struct Entries));
        map->entry[i].size=0;
    }
}

// insert a key value pair
void hash_insert(struct HashMap* map,void* key,void* val){
    usize hashed=map->hasher(key);
    struct Entry* entry=map->entry+(hashed%B);

    entry->list[entry->size].key=key;
    entry->list[entry->size++].val=val;
    if(entry->size==entry->cap){
        entry->cap*=2;
        entry->list=realloc(entry->list,sizeof(struct Entries)*entry->cap);
    }
}

// insert get pointer of key, return NULL if not found
void* hash_get(struct HashMap* map,void* key){
    usize hashed=map->hasher(key);
    struct Entry* entry=map->entry+(hashed%B);
    
    for(size_t i=0;i<(entry->size);i++){
        if (map->eq(entry->list[i].key,key)){
            return entry->list[i].val;
        }
    }
    return NULL;
}

// insert get pointer of key, return NULL if not pop
void* hash_pop(struct HashMap* map,void* key){
    usize hashed=map->hasher(key);
    struct Entry* entry=map->entry+(hashed%B);
    
    for(size_t i=0;i<(entry->size);i++){
        if (map->eq(entry->list[i].key,key)){
            void* tmp=entry->list[i].val;
            usize tail=(--entry->size);
            entry->list[i]=entry->list[tail];
            return entry->list[i].val;
        }
    }
    return NULL;
}
// struct Point{
//     usize x;
//     usize y;
// };

// bool eq(void* x,void* y){
//     struct Point* a=x;
//     struct Point* b=y;
//     return (a->x==b->x)&&(a->y==b->y);
// }
// usize hasher(void* a){
//     struct Point* p=a;
//     return (p->x)+(p->y)/2;
// }

// int test()
// {
//     struct HashMap map;
//     struct Point pa;
//     usize va=2;
//     pa.x=2;
//     pa.y=7;
//     struct Point pb;
//     usize vb=3;
//     pb.x=1;
//     pb.y=9;
//     hash_new(&map,hasher,eq);
//     hash_insert(&map,&pa,&va);
//     hash_insert(&map,&pb,&vb);

//     printf("pa has address of %zu\npb has address of %zu\n",&pa,&pb);

//     usize * assert=hash_get(&map,&pb);
//     printf("address: %zu\n",assert);
//     printf("value: %zu\n",*assert);

//     return 0;
// }