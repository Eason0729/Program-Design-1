#include "rust.h"

struct HashMap;

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

usize display_submask(struct SizedSubmask *mask);
usize display_ip(struct SizedSubmask *mask);
void parse_submask(char* cstr, struct SizedSubmask *mask);
void parse_ip(char* cstr, union Submask *mask);
struct SizedSubmask* scale(union Submask* mask);
struct SizedSubmask* clone_submask(struct SizedSubmask *mask);
bool reduce_submask(struct SizedSubmask* source);

struct State{
    struct Node* head;
    struct HashMap* hashmap;
};