#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 20 位图实现 Bloom 过滤器
 * 需求：m=100 位图，k=3 个哈希函数；插入 "apple"、"banana"，查询示例
 */

typedef struct {
    unsigned char *bits;
    size_t m; /* 位图大小（比特） */
} Bloom;

static Bloom *bloom_create(size_t m) {
    Bloom *bf = (Bloom *)malloc(sizeof(Bloom));
    if (bf == NULL) {
        return NULL;
    }
    bf->m = m;
    bf->bits = (unsigned char *)calloc((m + 7) / 8, sizeof(unsigned char));
    if (bf->bits == NULL) {
        free(bf);
        return NULL;
    }
    return bf;
}

static void bloom_free(Bloom *bf) {
    if (bf == NULL) {
        return;
    }
    free(bf->bits);
    free(bf);
}

/* 位操作 */
static void set_bit(unsigned char *bm, size_t idx) {
    bm[idx / 8] |= (unsigned char)(1u << (idx % 8));
}
static int test_bit(const unsigned char *bm, size_t idx) {
    return (bm[idx / 8] >> (idx % 8)) & 1u;
}

/* 三个简单哈希：sum(c*k) % m */
static size_t hash_k(const char *s, size_t m, int k) {
    size_t sum = 0;
    while (*s != '\0') {
        sum += (size_t)(unsigned char)(*s) * (size_t)k;
        s++;
    }
    return sum % m;
}

static void bloom_add(Bloom *bf, const char *s) {
    for (int k = 1; k <= 3; ++k) {
        set_bit(bf->bits, hash_k(s, bf->m, k));
    }
}

static int bloom_maybe_contains(Bloom *bf, const char *s) {
    for (int k = 1; k <= 3; ++k) {
        if (!test_bit(bf->bits, hash_k(s, bf->m, k))) {
            return 0;
        }
    }
    return 1;
}

int main(void) {
    const size_t m = 100; /* 位图大小 */
    Bloom *bf = bloom_create(m);
    if (!bf) {
        fprintf(stderr, "bloom create failed\n");
        return 1;
    }

    /* 插入元素："apple"、"banana" */
    bloom_add(bf, "apple");
    bloom_add(bf, "banana");

    /* 查询元素："apple"（应存在）、"orange"（可能存在误判） */
    int apple = bloom_maybe_contains(bf, "apple");
    int grape = bloom_maybe_contains(bf, "grape"); /* 未插入，可能误判 */

    printf("apple exists: %d\n", apple); /* 必须为 1（无假阴性） */
    printf("grape exists: %d\n", grape); /* 允许 0 或 1（可能误判） */

    bloom_free(bf);
    return 0;
}
