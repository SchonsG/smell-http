#ifndef CACHE_H
#define CACHE_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100

// Node structure for doubly linked list
typedef struct Node {
    const char *key;
    char* value;
    struct Node *prev, *next;
} Node;

// Cache structure
typedef struct LRUCache {
    int capacity, size; // cache limit and current number of stored elements
    struct Node *head, *tail; // track the most and least recently used nodes
} LRUCache;

typedef struct HashTable {
    Node* table[HASH_SIZE]; // Array of node pointers
} HashTable;

typedef struct CacheManager {
    LRUCache* cache;
    HashTable* ht;
} CacheManager;

CacheManager* create_manager_cache(int capacity);
char* get_from_cache(LRUCache* cache, HashTable* hash_table, const char* key);
void insert_into_cache(LRUCache* cache, HashTable* hash_table, const char* key, char* value);

#endif
