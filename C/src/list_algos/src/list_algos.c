#include "list_algos.h"
#include <string.h>
#include <stdlib.h>
inline int ascending_order(const void *str_1, const void *str_2) {

    int a = atoi((char *)str_1);
    int b = atoi((char *)str_2);

    return a - b;
}

inline int descending_order(const void *str_1, const void *str_2) {
    
    int a = atoi((char *)str_1);
    int b = atoi((char *)str_2);
    
    return b - a;
}

void List_bubble_sort(List *list, List_compare cmp) {

    check(list != NULL, "List is NULL.");
    check(cmp != NULL, "Compare function is NULL.");

    int n = list->count;
    while (n > 0) {
        ListNode *node = list->first;
        for (int i = 0; i < n - 1; i++) {
            if (cmp(node->value, node->next->value) > 0) {
                void *temp = node->value;
                node->value = node->next->value;
                node->next->value = temp;
            }
            node = node->next;
        }
        n--;
    }

error:
    return;
}

List *List_merge(List *left, List *right, List_compare cmp) {

    List *result = List_create();
    check_mem(result);

    while (left->first && right->first) {
        if (cmp(left->first->value, right->first->value) < 0) {
            List_push(result, left->first->value);
            left->first = left->first->next;
        } else {
            List_push(result, right->first->value);
            right->first = right->first->next;
        }
    }

    while (left->first) {
        List_push(result, left->first->value);
        left->first = left->first->next;
    }

    while (right->first) {
        List_push(result, right->first->value);
        right->first = right->first->next;
    }

    return result;

error:
    return NULL;
}  

void List_merge_sort(List *list, List_compare cmp) {

    check(list != NULL, "List is NULL.");
    check(cmp != NULL, "Compare function is NULL.");

    if (list->count <= 1) {
        return;
    }

    List *left = List_create();
    check_mem(left);
    List *right = List_create();
    check_mem(right);

    ListNode *node = list->first;
    int middle = list->count / 2;
    for (int i = 0; i < middle; i++) {
        List_push(left, node->value);
        node = node->next;
    }
    for (int i = middle; i < list->count; i++) {
        List_push(right, node->value);
        node = node->next;
    }

    List_merge_sort(left, cmp);
    List_merge_sort(right, cmp);

    List *result = List_merge(left, right, cmp);
    list->first = result->first;
    list->last = result->last;
    list->count = result->count;

    free(left);
    free(right);

error:
    return;
}

