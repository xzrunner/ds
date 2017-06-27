#include "ds_imap.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define NOT_IN_USE (0)
#define IN_USE     (1)
#define DELETED    (2)

static void
rehash(imap_t *imap, int key, int value) {
    int i;
    int count = 0;
    for(i=0; i<imap->size; ++i) {
        if(imap->hash[i].inuse == IN_USE) {
            count++;
        }
    }
    count++; /* for (key,vlaue) in arg */

    int oldsize = imap->size;
    int newsize = ((count << 1) <= oldsize) ? oldsize :
                  (oldsize <= 0) ? 1 :
                  (oldsize << 1);
    printf("[IMAP] rehash count:%d oldsize:%d newsize:%d\n", count, oldsize, newsize);
    imap_node_t * oldhash = imap->hash;
    imap_node_t * newhash = (imap_node_t *)malloc(newsize * sizeof(imap_node_t));
    memset(newhash, 0, newsize * sizeof(imap_node_t));
    imap->size = newsize;
    imap->hash = newhash;
    imap->lastfree = newhash + newsize;

    if(oldhash) {
        for(i=0; i<oldsize; ++i) {
            if(oldhash[i].inuse == IN_USE) {
                imap_set(imap, oldhash[i].key, oldhash[i].value);
            }
        }
        free(oldhash);
    }
    imap_set(imap, key, value);
}

static imap_node_t *
get_free_node(imap_t *imap) {
    while(imap->lastfree > imap->hash) {
        imap->lastfree--;
        if(imap->lastfree->inuse != IN_USE) {
            return imap->lastfree;
        }
    }
    return NULL;
}

void
imap_reset(imap_t *imap) {
    if(imap->hash) {
        memset(imap->hash, 0, sizeof(imap_node_t) * imap->size);
        imap->lastfree = imap->hash + imap->size;
    }
}

void
imap_free(imap_t *imap) {
    if(imap->hash) {
        free(imap->hash);
        imap->size = 0;
        imap->hash = NULL;
        imap->lastfree = NULL;
    }
}

void
imap_set(imap_t *imap, int key, int value) {
    if(imap->size <= 0) {
        rehash(imap, key, value);
        return;
    }
    int mp = key % imap->size;
    imap_node_t *node = &imap->hash[mp];
    if(node->inuse == IN_USE) {
        imap_node_t *free = get_free_node(imap);
        if(!free) {
            rehash(imap, key, value);
            return;
        }
        int mp2 = node->key % imap->size;
        if(mp2 == mp) {
            free->key = key;
            free->value = value;
            free->inuse = IN_USE;
            free->next = node->next;
            node->next = free - imap->hash;
        } else {
            free->key = node->key;
            free->value = node->value;
            free->inuse = IN_USE;
            free->next = node->next;
            node->key = key;
            node->value = value;
            node->next = free - imap->hash;
        }
    } else {
        if(node->inuse == NOT_IN_USE) {
            node->next = -1;
        }
        node->key = key;
        node->value = value;
        node->inuse = IN_USE;
    }
}

static imap_node_t *
find_node(imap_t *imap, int key) {
    if(imap->size <= 0) {
        return NULL;
    }
    int mp = key % imap->size;
    imap_node_t *node = &imap->hash[mp];
    while(1) {
        if(node->key == key && node->inuse == IN_USE) {
            return node;
        }
        if(node->inuse == NOT_IN_USE) { break; }
        if(node->next < 0) { break; }
        node = &imap->hash[node->next];
    }
    return NULL;
}

int
imap_get(imap_t *imap, int key, int *value) {
    imap_node_t *node = find_node(imap, key);
    if(node) {
        if(value) { *value = node->value; }
        return 1;
    } else {
        return 0;
    }
}

int
imap_del(imap_t *imap, int key) {
    imap_node_t *node = find_node(imap, key);
    if(node) {
        node->inuse = DELETED;
        return 1;
    } else {
        return 0;
    }
}

void
imap_traverse(imap_t *imap, imap_traverse_func_t cb) {
    int i;
    for(i=0; i<imap->size; ++i) {
        imap_node_t * node = &imap->hash[i];
        if(node->inuse == IN_USE) {
            cb(node->key, node->value);
        }
    }
}

