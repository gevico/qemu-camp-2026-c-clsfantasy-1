#include <stdio.h>
#include <stdlib.h>

/*
 * 19 字符串分割器（类似 strtok_r）
 * 目标：实现线程安全的字符串分割函数，不依赖静态全局状态
 * 原型：char* strtok_r(char *str, const char *delim, char **saveptr)
 * 示例：输入 "hello,world test"，分隔符 ", " → 依次得到 hello、world、test
 */

/* 判断字符 c 是否在分隔符集合 delim 中 */
static int is_delim(char c, const char *delim) {
    for (const char *p = delim; *p != '\0'; ++p) {
        if (*p == c) {
            return 1;
        }
    }
    return 0;
}

/* 线程安全版本：通过 saveptr 维护调用状态，不使用静态变量 */
char *strtok_r(char *str, const char *delim, char **saveptr) {
    char *start = str != NULL ? str : *saveptr;
    if (start == NULL) {
        return NULL;
    }

    while (*start != '\0' && is_delim(*start, delim)) {
        start++;
    }
    if (*start == '\0') {
        *saveptr = start;
        return NULL;
    }

    char *end = start;
    while (*end != '\0' && !is_delim(*end, delim)) {
        end++;
    }

    if (*end == '\0') {
        *saveptr = end;
        return start;
    }

    *end = '\0';
    *saveptr = end + 1;
    return start;
}

int main(void) {
    char buf[] = "hello,world test";
    const char *delim = ", ";
    char *save = NULL;

    char *tok = strtok_r(buf, delim, &save);
    while (tok) {
        printf("%s\n", tok);
        tok = strtok_r(NULL, delim, &save);
    }
    return 0;
}
