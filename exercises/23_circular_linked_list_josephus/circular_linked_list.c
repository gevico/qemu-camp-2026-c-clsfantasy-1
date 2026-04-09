#include "circular_linked_list.h"

#include <stdio.h>
#include <stdlib.h>

Node* create_circular_list(int n) {
    if (n <= 0) {
        return NULL;
    }

    Node* head = NULL;
    Node* tail = NULL;
    for (int i = 1; i <= n; ++i) {
        Node* node = (Node*)malloc(sizeof(Node));
        if (node == NULL) {
            free_list(head);
            return NULL;
        }
        node->id = i;
        node->next = NULL;
        if (head == NULL) {
            head = node;
        } else {
            tail->next = node;
        }
        tail = node;
    }
    tail->next = head;
    return head;
}

void free_list(Node* head) {
    if (head == NULL) {
        return;
    }

    Node* current = head->next;
    while (current != NULL && current != head) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    free(head);
}
