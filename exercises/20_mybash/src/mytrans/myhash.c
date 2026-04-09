// hash_table.c
#include "myhash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *dup_string(const char *text) {
  size_t length = strlen(text) + 1;
  char *copy = malloc(length);
  if (copy != NULL) {
    memcpy(copy, text, length);
  }
  return copy;
}

// djb2 哈希函数（经典字符串哈希，分布均匀）
unsigned long hash_function(const char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c; // hash * 33 + c
  return hash;
}

// 创建哈希表
HashTable *create_hash_table() {
  HashTable *table = malloc(sizeof(HashTable));
  if (!table)
    return NULL;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    table->buckets[i] = NULL;
  }
  return table;
}

// 释放单个节点
void free_node(HashNode *node) {
  if (node) {
    free(node->key);
    free(node->value);
    free(node);
  }
}

// 释放整个哈希表
void free_hash_table(HashTable *table) {
  if (!table)
    return;
  for (int i = 0; i < HASH_TABLE_SIZE; i++) {
    HashNode *curr = table->buckets[i];
    while (curr) {
      HashNode *tmp = curr;
      curr = curr->next;
      free_node(tmp);
    }
  }
  free(table);
}

// 插入键值对
int hash_table_insert(HashTable *table, const char *key, const char *value) {
  if (!table || !key || !value)
    return 0;

  unsigned long hash = hash_function(key) % HASH_TABLE_SIZE;
  HashNode *node = table->buckets[hash];

  while (node != NULL) {
    if (strcmp(node->key, key) == 0) {
      free(node->value);
      node->value = dup_string(value);
      return node->value != NULL;
    }
    node = node->next;
  }

  node = malloc(sizeof(HashNode));
  if (!node)
    return 0;

  node->key = dup_string(key);
  node->value = dup_string(value);
  if (!node->key || !node->value) {
    free_node(node);
    return 0;
  }
  node->next = table->buckets[hash];
  table->buckets[hash] = node;

  return 1;
}

// 查找键
const char *hash_table_lookup(HashTable *table, const char *key) {
  if (!table || !key)
    return NULL;

  unsigned long hash = hash_function(key) % HASH_TABLE_SIZE;
  HashNode *node = table->buckets[hash];

  while (node != NULL) {
    if (strcmp(node->key, key) == 0)
      return node->value;
    node = node->next;
  }

  return NULL; // 未找到
}
