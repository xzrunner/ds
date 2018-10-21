#include "ds_stack.h"

#include <stdlib.h>
#include <string.h>

struct ds_stack {
	void* data;
	size_t data_sz;

	int size;
	int capacity;
};

struct ds_stack*
ds_stack_create(int cap, size_t data_sz) {
	if (cap <= 0) {
		return NULL;
	}

	struct ds_stack* array = (struct ds_stack*)malloc(sizeof(struct ds_stack));
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
ds_stack_release(struct ds_stack* stack) {
	free(stack->data);
	free(stack);
}

bool
ds_stack_empty(struct ds_stack* stack) {
	return stack->size == 0;
}

void
ds_stack_push(struct ds_stack* stack, void* data) {
	if (stack->size == stack->capacity) {
		int cap = stack->capacity * 2;
		stack->capacity = cap;

		void* new_data = malloc(stack->capacity * stack->data_sz);
		memcpy(new_data, stack->data, stack->size * stack->data_sz);
		free(stack->data);
		stack->data = new_data;
	}

	memcpy((char*)stack->data + stack->data_sz * stack->size, data, stack->data_sz);
	++stack->size;
}

void*
ds_stack_top(struct ds_stack* stack) {
	if (!ds_stack_empty(stack)) {
		return (char*)stack->data + stack->data_sz * (stack->size - 1);
	} else {
		return NULL;
	}
}

void
ds_stack_pop(struct ds_stack* stack) {
	if (!ds_stack_empty(stack)) {
		--stack->size;
	}
}
