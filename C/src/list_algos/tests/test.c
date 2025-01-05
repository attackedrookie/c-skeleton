#include "minunit.h"
#include "../src/list_algos.h"
#include <assert.h>
#include <string.h>



char *test_bubble_sort()
{
    List *list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    List_push(list, "15");
    List_push(list, "1");
    List_push(list, "6");
    List_push(list, "29");
    mu_assert(List_count(list) == 4, "list push failed.");
    
    List_bubble_sort(list, ascending_order); // 升序排序

    mu_assert(strcmp(List_first(list), "1") == 0, "Bubble sort failed.");
    mu_assert(strcmp(list->first->next->value, "6") == 0, "Bubble sort failed.");
    mu_assert(strcmp(List_last(list), "29") == 0, "Bubble sort failed.");

    List_bubble_sort(list, descending_order); // 降序排序

    mu_assert(strcmp(List_first(list), "29") == 0, "Bubble sort failed.");
    mu_assert(strcmp(list->first->next->value, "15") == 0, "Bubble sort failed.");
    mu_assert(strcmp(List_last(list), "1") == 0, "Bubble sort failed.");

    List_destroy(list);

    return NULL;
}

char *test_merge_sort()
{
    List *list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    List_push(list, "15");
    List_push(list, "1");
    List_push(list, "6");
    List_push(list, "29");
    mu_assert(List_count(list) == 4, "list push failed.");
    
    List_merge_sort(list, ascending_order); // 升序排序

    mu_assert(strcmp(List_first(list), "1") == 0, "Merge sort failed.");
    mu_assert(strcmp(list->first->next->value, "6") == 0, "Merge sort failed.");
    mu_assert(strcmp(List_last(list), "29") == 0, "Merge sort failed.");

    List_merge_sort(list, descending_order); // 降序排序

    mu_assert(strcmp(List_first(list), "29") == 0, "Merge sort failed.");
    mu_assert(strcmp(list->first->next->value, "15") == 0, "Merge sort failed.");
    mu_assert(strcmp(List_last(list), "1") == 0, "Merge sort failed.");

    List_destroy(list);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);