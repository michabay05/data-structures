#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} LLNode;

typedef struct {
    LLNode* head;
    size_t length;
} LL;

LL ll_init() {
    return (LL) {
        .head = NULL,
        .length = 0,
    };
}

void ll_append(LL* ll, int val) {
    ll->length++;
    LLNode* temp = (LLNode*)malloc(sizeof(LLNode));
    temp->data = val;
    temp->next = NULL;
    if (ll->head == NULL) {
        ll->head = temp;
        return;
    }
    LLNode* current = ll->head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = temp;
}

void ll_insert(LL* ll, int val, size_t index) {
    ll->length++;
    assert(index < ll->length);
    if (ll->head == NULL) {
        ll_append(ll, val);
        return;
    }
    LLNode* temp = (LLNode*)malloc(sizeof(LLNode));
    temp->data = val;
    LLNode* current = ll->head;
    LLNode* prev_next;
    size_t count = 0;
    while (current != NULL) {
        if (count == index - 1) {
            prev_next = current->next;
            current->next = temp;
        } else if (count == index) {
            temp->next = prev_next;
            break;
        } else {
            current = current->next;
        }
        count += 1;
    }
}

void ll_print(const LL* const ll) {
    if (ll->length == 0) {
        printf("[]\n");
        return;
    }
    printf("[");
    LLNode* current = ll->head;
    size_t count = 0;
    while (current != NULL) {
        printf("%d", current->data);
        if (count < ll->length - 1) {
            printf(" > ");
        }
        current = current->next;
        count += 1;
    }
    printf("]\n");
}

void ll_deinit(LL* ll) {
    LLNode* current = ll->head;
    while (current != NULL) {
        LLNode* temp = current;
        current = current->next;
        free(temp);
    }
}

int main(void) {
    LL ll = ll_init();
    ll_append(&ll, -100);
    for (int i = -500; i < 1000; i++) {
        ll_append(&ll, i * 2);
    }

    ll_deinit(&ll);
    return EXIT_SUCCESS;
}
