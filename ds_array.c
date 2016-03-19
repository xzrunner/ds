#include "ds_array.h"

#include <stdlib.h>
#include <string.h>

struct ds_array {
	void* data;
	size_t data_sz;

	int size;
	int capacity;
};

struct ds_array* 
ds_array_create(int cap, size_t data_sz) {
	if (cap <= 0) {
		return NULL;
	}

	struct ds_array* array = (struct ds_array*)malloc(sizeof(struct ds_array));
	if (!array) {
		return NULL;
	}

	array->data = malloc(data_sz * cap);
	array->data_sz = data_sz;

	array->size = 0;
	array->capacity = cap;

	return array;
}

void 
ds_array_release(struct ds_array* array) {
	free(array->data);
	free(array);
}

int 
ds_array_size(struct ds_array* array) {
	return array->size;
}

void* 
ds_array_fetch(struct ds_array* array, int idx) {
	if (idx < 0 || idx >= array->size) {
		return NULL;
	} else {
		return (char*)array->data + array->data_sz * idx;
	}
}

void 
ds_array_add(struct ds_array* array, void* data) {
	if (array->size == array->capacity) {
		int cap = array->capacity * 2;
		array->capacity = cap;

		void* new_data = malloc(array->capacity * array->data_sz);
		memcpy(new_data, array->data, array->size * array->data_sz);
		free(array->data);
		array->data = new_data;
	}

	memcpy((char*)array->data + array->data_sz * array->size, data, array->data_sz);
	++array->size;
}

void 
ds_array_clear(struct ds_array* array) {
	array->size = 0;
}