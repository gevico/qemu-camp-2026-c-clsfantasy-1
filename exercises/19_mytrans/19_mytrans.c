// main.c
#include "myhash.h"
#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

void to_lowercase(char *str) {
  for (; *str; ++str) {
    *str = tolower((unsigned char)*str);
  }
}

int main() {
  HashTable *table = create_hash_table();
  if (!table) {
    fprintf(stderr, "无法创建哈希表\n");
    return 1;
  }

  printf("=== 哈希表版英语翻译器（支持百万级数据）===\n");
  uint64_t dict_count = 0;
  if (load_dictionary("dict.txt", table, &dict_count) != 0) {
    fprintf(stderr, "加载词典失败，请确保 dict.txt 存在。\n");
    free_hash_table(table);
    return 1;
  }
  printf("词典加载完成，共计%lu词条。\n", (unsigned long)dict_count);

  FILE *file = fopen("text.txt", "r");
  if (file == NULL) {
    fprintf(stderr, "无法打开文件 text.txt。\n");
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

  fclose(file);
  free_hash_table(table);
  return 0;
}
