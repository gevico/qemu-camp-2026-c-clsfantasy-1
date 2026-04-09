// mytrans.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trim(char *str) {
  char *start = str;
  while (*start != '\0' && isspace((unsigned char)*start)) {
    start++;
  }

  char *end = start + strlen(start);
  while (end > start && isspace((unsigned char)*(end - 1))) {
    end--;
  }

  size_t length = (size_t)(end - start);
  memmove(str, start, length);
  str[length] = '\0';
}

int load_dictionary(const char *filename, HashTable *table,
                    uint64_t *dict_count) {
  FILE *file = fopen(filename, "r");
  if (!file) {
    perror("无法打开词典文件");
    return -1;
  }

  char line[1024];
  char current_word[100] = {0};
  char current_translation[1024] = {0};
  int in_entry = 0;

  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';
    trim(line);

    if (line[0] == '\0') {
      continue;
    }

    if (line[0] == '#') {
      if (in_entry && current_word[0] != '\0' && current_translation[0] != '\0') {
        if (hash_table_insert(table, current_word, current_translation)) {
          (*dict_count)++;
        }
      }

      strncpy(current_word, line + 1, sizeof(current_word) - 1);
      current_word[sizeof(current_word) - 1] = '\0';
      trim(current_word);
      current_translation[0] = '\0';
      in_entry = 1;
    } else if (strncmp(line, "Trans:", 6) == 0 && in_entry) {
      strncpy(current_translation, line + 6, sizeof(current_translation) - 1);
      current_translation[sizeof(current_translation) - 1] = '\0';
      trim(current_translation);

      if (current_word[0] != '\0' && current_translation[0] != '\0') {
        if (hash_table_insert(table, current_word, current_translation)) {
          (*dict_count)++;
        }
      }

      current_word[0] = '\0';
      current_translation[0] = '\0';
      in_entry = 0;
    }
  }

  if (in_entry && current_word[0] != '\0' && current_translation[0] != '\0') {
    if (hash_table_insert(table, current_word, current_translation)) {
      (*dict_count)++;
    }
  }

  fclose(file);
  return 0;
}

void to_lowercase(char *str) {
  for (; *str; ++str)
    *str = tolower((unsigned char)*str);
}

int __cmd_mytrans(const char* filename) {
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");
  uint64_t dict_count = 0;
  if (load_dictionary("src/mytrans/dict.txt", table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%ld词条。\n", dict_count);

  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 dict.txt。\n");
    free_hash_table(table);
    return 1;
  }

  char line[256];
  while (fgets(line, sizeof(line), file) != NULL) {
    line[strcspn(line, "\n")] = '\0';

    if (strlen(line) == 0) {
        continue;
    }

    char *word = strtok(line, " ");
    while (word != NULL) {
      char normalized[256];
      strncpy(normalized, word, sizeof(normalized) - 1);
      normalized[sizeof(normalized) - 1] = '\0';
      to_lowercase(normalized);

      size_t start = 0;
      while (normalized[start] != '\0' && ispunct((unsigned char)normalized[start])) {
        start++;
      }

      size_t end = strlen(normalized);
      while (end > start && ispunct((unsigned char)normalized[end - 1])) {
        end--;
      }

      if (end > start) {
        memmove(normalized, normalized + start, end - start);
        normalized[end - start] = '\0';

        const char *translation = hash_table_lookup(table, normalized);
        printf("原文: %s\t", normalized);
        if (translation) {
            printf("翻译: %s\n", translation);
        } else {
            printf("未找到该单词的翻译。\n");
        }
      }

      word = strtok(NULL, " ");
    }
  }

  free_hash_table(table);
  return 0;
}