#include "cache/cache.h"

Node* create_node(const char* key, char* value) {
    Node* node = malloc(sizeof(*node));
    node->key = strdup(key);
    node->value = strdup(value);
    node->next = NULL;
    node->prev = NULL;

    return node;
}

void insert_at_front(LRUCache* cache, Node* node) {
    node->next = cache->head;
    node->prev = NULL;

    if (cache->head) {
        cache->head->prev = node;
    }

    cache->head = node;

    if (!cache->tail) {
        cache->tail = node;
    }
}

void remove_node(LRUCache* cache, Node* node) {
    if (cache->head == node) {
        cache->head = node->next;
    } else {
        node->prev->next = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        cache->tail = node->prev;
    }
}

unsigned int hash_function(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + (*key); // Simple hash function
        key++;
    }
    return hash % HASH_SIZE;
}

void insert_into_hash_table(HashTable* hash_table, Node* node) {
    unsigned int hash = hash_function(node->key);
    hash_table->table[hash] = node;
}

Node* lookup(HashTable* hash_table, const char* key) {
    unsigned int index = hash_function(key);
    return hash_table->table[index]; // Return cached node pointer
}

void remove_from_hash_table(HashTable* hash_table, const char* key) {
    unsigned int index = hash_function(key);
    hash_table->table[index] = NULL; // Clear the entry
}

void evict_lru(LRUCache* cache, HashTable* hash_table) {
    if (cache->tail) {
        remove_from_hash_table(hash_table, cache->tail->key); // Remove from hash table
        remove_node(cache, cache->tail); // Remove from linked list
    }
}

void insert_into_cache(LRUCache* cache, HashTable* hash_table, const char* key, char* value) {
    Node* existing_node = lookup(hash_table, key);

    // The cache already exists
    if (existing_node) {
        existing_node->value = value;
        remove_node(cache, existing_node);
        insert_at_front(cache, existing_node);
        return;
    }

    if (cache->size >= cache->capacity) {
        evict_lru(cache, hash_table);
        cache->size--;
    }

    // Create new node and insert it
    Node* new_node = create_node(key, value);
    insert_at_front(cache, new_node);
    insert_into_hash_table(hash_table, new_node);
    cache->size++; // Increase cache size
}

char* get_from_cache(LRUCache* cache, HashTable* hash_table, const char* key) {
    Node* node = lookup(hash_table, key);
    
    if (node) {
        // Move node to front to mark as most recently used
        remove_node(cache, node);
        insert_at_front(cache, node);
        return (node->value);
    }
    
    return NULL; // Not found
}

CacheManager* create_manager_cache(int capacity) {
    CacheManager* manager = malloc(sizeof(*manager));
    manager->cache = malloc(sizeof(LRUCache));
    manager->cache->capacity = capacity;
    manager->cache->size = 0;
    manager->cache->head = NULL;
    manager->cache->tail = NULL;

    manager->ht = malloc(sizeof(HashTable));
    memset(manager->ht->table, 0, sizeof(manager->ht->table)); // Initialize hash table

    return manager;
}
