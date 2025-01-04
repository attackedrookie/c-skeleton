#include "list.h"
#include "dbg.h"
#include <string.h>


List *List_create()
{
    return calloc(1, sizeof(List));
}

// 清除 List 结构体本身，但不释放 value 指向的内存
void List_destroy(List *list) {

    if (list == NULL) return; // 避免空指针错误

    ListNode *node = list->first;
    while (node) {
        ListNode *next = node->next; // 保存下一个节点的指针
        free(node); // 释放当前节点
        node = next; // 移动到下一个节点
    }

    free(list); // 释放 List 结构本身
}

// 不清除 List 结构体本身，但释放 value 指向的内存和节点本身
void List_clear(List *list) {
    if (list == NULL) return;

    ListNode *node = list->first;
    while (node) {
        ListNode *next = node->next;
        if (node->value) {
            free(node->value); // 只释放 value 指向的内存 (如果 value 是动态分配的)
        }
        free(node); // 释放节点本身
        node = next;
    }

    list->first = NULL; // 将 list 恢复到空状态
    list->last = NULL;
    list->count = 0;
}


void List_clear_destroy(List *list) {
    List_clear(list);
    free(list);
}

void List_push(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->last == NULL) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        node->prev = list->last;
        node->next = NULL;
        list->last = node;
    }

    list->count++;

error:
    return;
}

void *List_pop(List *list)
{
    ListNode *node = list->last;
    return node != NULL ? List_remove(list, node) : NULL;
}

void List_unshift(List *list, void *value)
{
    ListNode *node = calloc(1, sizeof(ListNode));
    check_mem(node);

    node->value = value;

    if(list->first == NULL) {
        list->first = node;
        list->last = node;
    } else {
        node->next = list->first;
        list->first->prev = node;
        list->first = node;
    }

    list->count++;

error:
    return;
}

void *List_shift(List *list)
{
    ListNode *node = list->first;
    return node != NULL ? List_remove(list, node) : NULL;
}

void *List_remove(List *list, ListNode *node)
{
    void *result = NULL;

    check(list->first && list->last, "List is empty.");
    check(node, "node can't be NULL");

    if(node == list->first && node == list->last) {
        list->first = NULL;
        list->last = NULL;
    } else if(node == list->first) {
        list->first = node->next;
        check(list->first != NULL, "Invalid list, somehow got a first that is NULL.");
        list->first->prev = NULL;
    } else if (node == list->last) {
        list->last = node->prev;
        check(list->last != NULL, "Invalid list, somehow got a next that is NULL.");
        list->last->next = NULL;
    } else {
        ListNode *after = node->next;
        ListNode *before = node->prev;
        after->prev = before;
        before->next = after;
    }

    list->count--;
    result = node->value;
    free(node);

error:
    return result;
}

// 深拷贝
void *List_copy(List *list) {

    List *new_list = List_create();
    check_mem(new_list);
    ListNode *node = list->first;

    check(list->first, "List is empty.");   
    
    while (node) {
        // 深拷贝，而不是浅拷贝，使俩个指针指向同一块字符串内存
        char *new_value = strdup((char *)node->value); 
        List_push(new_list, new_value); 
        node = node->next;
    }
    new_list->count = list->count;

    return new_list;

error:
    return NULL;
}

// 浅拷贝
void *List_join(List *left, List *right) {

    check(left->last && right->first, "List is empty.");

    List *new_list = List_create();
    check_mem(new_list);

    left->last->next = right->first;
    right->first->prev = left->last;
    new_list->first = left->first;
    new_list->last = right->last;
    new_list->count = left->count + right->count;

    return new_list;

error:
    return NULL;
}

void List_split(List *list, List **left, List **right,int index) {

    check(list->first, "List is empty.");
    check(index >= 0, "Index out of range.");
    check(list->count > 1, "List is too short.");
    check(index < list->count, "Index out of range.");
    
    *left = List_create();
    check_mem(*left);
    *right = List_create();
    check_mem(*right);

    int i = 0;
    ListNode *node = list->first;
    while (node) {
        if (i < index) {
            List_push(*left, node->value);
        } else {
            List_push(*right,node->value);
        }
        node = node->next;
        i++;
    }
    (*left)->count = index;
    (*right)->count = list->count - index;

    List_destroy(list);

error:
    return;
}