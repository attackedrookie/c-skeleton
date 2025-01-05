#ifndef __list_algos_h__
#define __list_algos_h__

#include "list.h"
#include "dbg.h"

typedef int (*List_compare)(const void *a, const void *b);

int ascending_order(const void *str_1, const void *str_2);
int descending_order(const void *str_1, const void *str_2);

void List_bubble_sort(List *list, List_compare cmp);
void List_merge_sort(List *list, List_compare cmp);

List *List_merge(List *left, List *right, List_compare cmp);



#endif

