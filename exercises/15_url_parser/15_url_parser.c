#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

/**
 * URL参数解析器
 * 输入：包含http/https超链接的字符串
 * 输出：解析出所有的key-value键值对，每行显示一个
 */

int parse_url(const char* url) {
    int err = 0;

    const char *query = strchr(url, '?');
    if (query == NULL || *(query + 1) == '\0') {
        return -1;
    }

    size_t query_len = strlen(query + 1);
    char *buffer = malloc(query_len + 1);
    if (buffer == NULL) {
        return -1;
    }
    memcpy(buffer, query + 1, query_len + 1);

    char *pair = strtok(buffer, "&");
    while (pair != NULL) {
        char *equal = strchr(pair, '=');
        if (equal != NULL) {
            *equal = '\0';
            printf("key = %s, value = %s\n", pair, equal + 1);
        }
        pair = strtok(NULL, "&");
    }

    free(buffer);

exit:
    return err;
}

int main() {
    const char* test_url = "https://cn.bing.com/search?name=John&age=30&city=New+York";

    printf("Parsing URL: %s\n", test_url);
    printf("Parameters:\n");

    parse_url(test_url);

    return 0;
}