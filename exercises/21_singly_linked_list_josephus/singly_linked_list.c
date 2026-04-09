#include "singly_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

// 全局头指针
static link head = NULL;

// 创建新节点
link make_node(unsigned char item) {
    link p = (link)malloc(sizeof(struct node));
    if (p == NULL) {
        return NULL;
    }
    p->item = item;
    p->next = NULL;
    return p;
}

// 释放节点
void free_node(link p) { free(p); }

// 查找节点
link search(unsigned char key) {
    for (link p = head; p != NULL; p = p->next) {
        if (p->item == key) {
            return p;
        }
    }
    return NULL;
}

// 在链表头部插入节点
void insert(link p) {
    if (p == NULL) {
        return;
    }
    p->next = head;
    head = p;
}

// 删除指定节点
void delete(link p) {
    if (p == NULL || head == NULL) {
        return;
    }

    if (head == p) {
        head = head->next;
        free_node(p);
        return;
    }

    for (link prev = head; prev->next != NULL; prev = prev->next) {
        if (prev->next == p) {
            prev->next = p->next;
            free_node(p);
            return;
        }
    }
}

// 遍历链表
void traverse(void (*visit)(link)) {
    for (link p = head; p != NULL; p = p->next) {
        visit(p);
    }
}

// 销毁整个链表
void destroy(void) {
    link p = head;
    while (p != NULL) {
        link next = p->next;
        free_node(p);
        p = next;
    }
    head = NULL;
}

// 在链表头部推入节点
void push(link p) { insert(p); }

// 从链表头部弹出节点
link pop(void) {
    if (head == NULL) {
        return NULL;
    }
    link p = head;
    head = head->next;
    p->next = NULL;
    return p;
}

// 释放链表内存
void free_list(link list_head) {
    while (list_head != NULL) {
        link next = list_head->next;
        free_node(list_head);
        list_head = next;
    }
}
