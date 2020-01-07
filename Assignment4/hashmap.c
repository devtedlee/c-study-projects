#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "hashmap.h"

node_t* find_node_or_null(node_t* node, const char* key);

hashmap_t* init_hashmap_malloc(size_t length, int (*p_hash_func)(const char* key))
{
    hashmap_t* hashmap;

    hashmap = (hashmap_t*)malloc(sizeof(hashmap_t));

    hashmap->hash_func = p_hash_func;

    hashmap->plist = (node_t**)calloc(length, sizeof(node_t*));

    hashmap->length = length;

    return hashmap;
}

int add_key(hashmap_t* hashmap, const char* key, const int value)
{
    int code = 0;
    node_t* bucket;
    node_t* new_node;
    size_t key_len = strlen(key);

    if (key_len == 0) {
        return FALSE;
    }

    code = hashmap->hash_func(key);

    if (code > (int)hashmap->length) {
        code %= (int)hashmap->length;
    }

    if (hashmap->plist[code] == NULL) {
        hashmap->plist[code] = (node_t*)calloc(1, sizeof(node_t));
    }

    bucket = hashmap->plist[code];

    if (bucket->key != NULL) {
        bucket = find_node_or_null(bucket, key);
        if (bucket != NULL) {
            return FALSE;
        }

        bucket = hashmap->plist[code];

        while (bucket->next != NULL) {
            bucket = bucket->next;
        }
    }

    if (bucket->key == NULL) {
        new_node = bucket;
    } else {
        new_node = (node_t*)calloc(1, sizeof(node_t));
    }

    new_node->key = (char*)malloc(sizeof(char) * (key_len + 1));
    strncpy(new_node->key, key, key_len);
    new_node->key[key_len] = '\0';
    new_node->value = (int)value;

    if (bucket != new_node) {
        bucket->next = new_node;
    }

    return TRUE;
}

int get_value(hashmap_t* hashmap, const char* key)
{
    const int GET_VALUE_FAIL = -1;
    int code = 0;
    node_t* bucket;

    if (strlen(key) == 0) {
        return GET_VALUE_FAIL;
    }

    code = hashmap->hash_func(key);

    if (code > (int)hashmap->length) {
        code %= (int)hashmap->length;
    }

    bucket = hashmap->plist[code];
    if (bucket == NULL) {
        return GET_VALUE_FAIL;
    }

    bucket = find_node_or_null(bucket, key);
    if (bucket != NULL) {
        return bucket->value;
    }

    return GET_VALUE_FAIL;
}

int update_value(hashmap_t* hashmap, const char* key, int value)
{
    int code = 0;
    node_t* bucket;

    if (strlen(key) == 0) {
        return FALSE;
    }

    code = hashmap->hash_func(key);

    if (code > (int)hashmap->length) {
        code %= (int)hashmap->length;
    }

    bucket = hashmap->plist[code];
    if (bucket == NULL) {
        return FALSE;
    }

    bucket = find_node_or_null(bucket, key);
    if (bucket == NULL) {
        return FALSE;
    }

    bucket->value = value;

    return TRUE;
}

int remove_key(hashmap_t* hashmap, const char* key)
{
    int code = 0;
    node_t* bucket;
    node_t* del_node;

    if (strlen(key) == 0) {
        return FALSE;
    }

    code = hashmap->hash_func(key);

    if (code > (int)hashmap->length) {
        code %= (int)hashmap->length;
    }

    bucket = hashmap->plist[code];
    if (bucket == NULL) {
        return FALSE;
    }

    if (bucket->next == NULL && strcmp(bucket->key, key) != 0) {
        return FALSE;
    }

    if (strcmp(bucket->key, key) != 0) {
        while (bucket->next != NULL) {
            if (strcmp(bucket->next->key, key) == 0) {
                break;
            }
            
            bucket = bucket->next;

            if (bucket->next == NULL) {
                return FALSE;
            }
        }
    }

    del_node = bucket;
    del_node->key = bucket->key;

    if (bucket->next != NULL) {
        if (hashmap->plist[code] == bucket) {
            del_node = hashmap->plist[code];
            del_node->key = hashmap->plist[code]->key;

            hashmap->plist[code] = bucket->next;
            hashmap->plist[code]->key = bucket->next->key;
        } else {
            bucket = bucket->next;
            bucket->key = bucket->next->key;
        }
    }

    if (del_node == hashmap->plist[code] && bucket->next == NULL) {
        free(hashmap->plist[code]->key);
        hashmap->plist[code]->key = NULL;
        free(hashmap->plist[code]);
        hashmap->plist[code] = NULL;
    } else {
        free(del_node->key);
        del_node->key = NULL;
        free(del_node);
        del_node = NULL;
    }

    return TRUE;
}

void destroy(hashmap_t* hashmap)
{
    size_t i = 0;

    for (i = 0; i < hashmap->length; ++i) {
        node_t* bucket = hashmap->plist[i];

        while (bucket != NULL) {
            node_t* temp_node = bucket->next;

            if (bucket->key != NULL) {
                free(bucket->key);
            }
            free(bucket);
            bucket = temp_node;
        }
    }

    free(hashmap->plist);

    free(hashmap);
}

node_t* find_node_or_null(node_t* node, const char* key)
{
    if (node->key == NULL) {
        return NULL;
    }

    while (node != NULL) {
        if (strcmp(node->key, key) == 0) {
            return node;
        }
        node = node->next;
    }

    return NULL;
}
