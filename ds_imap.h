#ifndef LR_IMAP_H
#define LR_IMAP_H

#include <stdint.h>

typedef struct {
    int next;
    int key;
    int value;
    uint8_t inuse;
} imap_node_t;

typedef struct {
    int size;
    imap_node_t * hash;
    imap_node_t * lastfree;
} imap_t;

void imap_reset(imap_t *imap);
void imap_free(imap_t *imap);
void imap_set(imap_t *imap, int key, int value);
int imap_get(imap_t *imap, int key, int *value);
int imap_del(imap_t *imap, int key);

static inline int
imap_check(imap_t *imap, int key) {
    return imap_get(imap, key, NULL);
}

typedef void (*imap_traverse_func_t)(int key, int value);
void imap_traverse(imap_t *imap, imap_traverse_func_t cb);

#endif
