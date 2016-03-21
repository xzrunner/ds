#ifdef __cplusplus
extern "C"
{
#endif

#ifndef data_structure_array_h
#define data_structure_array_h

#include <stddef.h>

struct ds_array;

struct ds_array* ds_array_create(int cap, size_t data_sz);
void ds_array_release(struct ds_array*);

int ds_array_size(struct ds_array*);
void* ds_array_fetch(struct ds_array*, int idx);

const void* ds_array_data(struct ds_array*);

void ds_array_add(struct ds_array*, void* data);
void ds_array_clear(struct ds_array*);

#endif // data_structure_array_h

#ifdef __cplusplus
}
#endif