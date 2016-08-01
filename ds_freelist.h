#ifdef __cplusplus
extern "C"
{
#endif

#ifndef data_structure_freelist_h
#define data_structure_freelist_h

/**
 *  @brief
 *    struct type {
 *        ...
 *        struct type *prev, *next;
 *    };
 */

#define DS_FREELIST(type) \
	struct ds_freelist_##type { \
		struct type *freelist; \
		struct type *head, *tail; \
	};

#define DS_FREELIST_CREATE(type, list, cap, mem) do { \
	list.freelist = (struct type*)(mem); \
	for (int i = 0; i < cap; ++i) { \
		list.freelist[i].next = &list.freelist[i+1]; \
	} \
	list.freelist[cap - 1].next = NULL; \
	list.freelist[0].prev = NULL; \
	for (int i = 1; i < cap; ++i) { \
		list.freelist[i].prev = &list.freelist[i-1]; \
	} \
} while (0)

/**
 *  @remarks
 *    shouldn't pass list.head as node
 */
#define DS_FREELIST_DECONNECT_NODE(list, node) do { \
	if (list.head == node) { \
		list.head = node->next; \
	} \
	if (list.tail == node) { \
		list.tail = node->prev; \
	} \
	if (node->prev) { \
		node->prev->next = node->next; \
	} \
	if (node->next) { \
		node->next->prev = node->prev; \
	} \
} while (0)

#define DS_FREELIST_PUSH_NODE_TO_FREELIST(list, node) do { \
	DS_FREELIST_DECONNECT_NODE(list, node); \
	node->prev = NULL; \
	node->next = list.freelist; \
	if (list.freelist) { \
		list.freelist->prev = node; \
	} \
	list.freelist = node; \
} while (0)

#define DS_FREELIST_MOVE_NODE_TO_TAIL(list, node) do { \
	DS_FREELIST_DECONNECT_NODE(list, node); \
	if (!list.head) { \
		list.head = node; \
	} \
	node->prev = list.tail; \
	if (list.tail) { \
		list.tail->next = node; \
	} \
	node->next = NULL; \
	list.tail = node; \
} while (0)

#define DS_FREELIST_POP_NODE_FROM_FREELIST(list, node) do { \
	assert(list.freelist); \
	node = list.freelist; \
	list.freelist = node->next; \
	if (!list.head) { \
		assert(!list.tail); \
		list.head = list.tail = node; \
		node->prev = node->next = NULL; \
	} else { \
		assert(list.tail); \
		list.tail->next = node; \
		node->prev = list.tail; \
		node->next = NULL; \
		list.tail = node; \
	} \
} while (0)

#endif // data_structure_freelist_h

#ifdef __cplusplus
}
#endif