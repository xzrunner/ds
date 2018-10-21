#ifdef __cplusplus
extern "C"
{
#endif

#ifndef data_structure_stack_h
#define data_structure_stack_h

#include <stdbool.h>
#include <stddef.h>

struct ds_stack;

struct ds_stack* ds_stack_create(int cap, size_t data_sz);
void ds_stack_release(struct ds_stack*);

bool ds_stack_empty(struct ds_stack*);
void ds_stack_push(struct ds_stack*, void* data);
void* ds_stack_top(struct ds_stack*);
void ds_stack_pop(struct ds_stack*);

#endif // data_structure_stack_h

#ifdef __cplusplus
}
#endif