#ifdef __cplusplus
extern "C"
{
#endif

#ifndef data_structure_hash_h
#define data_structure_hash_h

#include <stdbool.h>

struct ds_hash;
struct ds_array;

struct ds_hash* ds_hash_create(int capacity, int hash_size, float rehash_weight,
	                               unsigned int (*hash_func)(int hash_sz, void* key),
								   bool (*equal_func)(void* key0, void* key1));
void ds_hash_release(struct ds_hash*);

void* ds_hash_query(struct ds_hash*, void* key);
void ds_hash_query_all(struct ds_hash*, void* key, struct ds_array* ret);

void ds_hash_insert(struct ds_hash*, void* key, void* val, bool force);
void* ds_hash_remove(struct ds_hash*, void* key);
void ds_hash_clear(struct ds_hash*);

unsigned int ds_string_hash_func(int hash_sz, void* key);
bool ds_string_equal_func(void* key0, void* key1);

#endif // data_structure_hash_h

#ifdef __cplusplus
}
#endif