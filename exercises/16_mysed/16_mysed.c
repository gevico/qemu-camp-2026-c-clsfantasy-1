#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_LENGTH 1024

int parse_replace_command(const char* cmd, char** old_str, char** new_str) {
    if (cmd[0] != 's' || cmd[1] != '/') {
        return -1;
    }

    const char *old_begin = cmd + 2;
    const char *old_end = strchr(old_begin, '/');
    if (old_end == NULL) {
        return -1;
    }

    const char *new_begin = old_end + 1;
    const char *new_end = strchr(new_begin, '/');
    if (new_end == NULL) {
        return -1;
    }

    size_t old_len = (size_t)(old_end - old_begin);
    size_t new_len = (size_t)(new_end - new_begin);

    *old_str = malloc(old_len + 1);
    *new_str = malloc(new_len + 1);
    if (*old_str == NULL || *new_str == NULL) {
        free(*old_str);
        free(*new_str);
        *old_str = NULL;
        *new_str = NULL;
        return -1;
    }

    memcpy(*old_str, old_begin, old_len);
    (*old_str)[old_len] = '\0';
    memcpy(*new_str, new_begin, new_len);
    (*new_str)[new_len] = '\0';

    return 0;
}

void replace_first_occurrence(char* str, const char* old, const char* new) {
    char *match = strstr(str, old);
    if (match == NULL) {
        return;
    }

    char buffer[MAX_LINE_LENGTH * 2];
    size_t prefix_len = (size_t)(match - str);
    size_t old_len = strlen(old);
    size_t new_len = strlen(new);
    size_t suffix_len = strlen(match + old_len);

    if (prefix_len + new_len + suffix_len >= sizeof(buffer)) {
        return;
    }

    memcpy(buffer, str, prefix_len);
    memcpy(buffer + prefix_len, new, new_len);
    memcpy(buffer + prefix_len + new_len, match + old_len, suffix_len + 1);
    strcpy(str, buffer);
}

int main(int argc, char* argv[]) {
    const char* replcae_rules = "s/unix/linux/";

    char line[MAX_LINE_LENGTH] = {"unix is opensource. unix is free os."};

    char* old_str = NULL;
    char* new_str = NULL;
    
    if (parse_replace_command(replcae_rules, &old_str, &new_str) != 0) {
        fprintf(stderr, "Invalid replace command format. Use 's/old/new/'\n");
        return 1;
    }

    
    replace_first_occurrence(line, old_str, new_str);
    fputs(line, stdout);

    free(old_str);
    free(new_str);
    return 0;
}
