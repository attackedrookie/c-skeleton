#include "minunit.h"
#include "../src/list.h"
#include <assert.h>

static List *list = NULL;
char *test1 = "test1 data";
char *test2 = "test2 data";
char *test3 = "test3 data";


char *test_create()
{
    list = List_create();
    mu_assert(list != NULL, "Failed to create list.");

    return NULL;
}


char *test_destroy()
{
    List_clear_destroy(list);
    return NULL;

}


char *test_push_pop()
{
    List_push(list, test1);
    mu_assert(List_last(list) == test1, "Wrong last value.");

    List_push(list, test2);
    mu_assert(List_last(list) == test2, "Wrong last value");

    List_push(list, test3);
    mu_assert(List_last(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on push.");

    char *val = List_pop(list);
    mu_assert(val == test3, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test2, "Wrong value on pop.");

    val = List_pop(list);
    mu_assert(val == test1, "Wrong value on pop.");
    mu_assert(List_count(list) == 0, "Wrong count after pop.");

    return NULL;
}

char *test_unshift()
{
    List_unshift(list, test1);
    mu_assert(List_first(list) == test1, "Wrong first value.");

    List_unshift(list, test2);
    mu_assert(List_first(list) == test2, "Wrong first value");

    List_unshift(list, test3);
    mu_assert(List_first(list) == test3, "Wrong last value.");
    mu_assert(List_count(list) == 3, "Wrong count on unshift.");

    return NULL;
}

char *test_remove()
{
    // we only need to test the middle remove case since push/shift
    // already tests the other cases

    char *val = List_remove(list, list->first->next);
    mu_assert(val == test2, "Wrong removed element.");
    mu_assert(List_count(list) == 2, "Wrong count after remove.");
    mu_assert(List_first(list) == test3, "Wrong first after remove.");
    mu_assert(List_last(list) == test1, "Wrong last after remove.");

    return NULL;
}


char *test_shift()
{
    mu_assert(List_count(list) != 0, "Wrong count before shift.");

    char *val = List_shift(list);
    mu_assert(val == test3, "Wrong value on shift.");

    val = List_shift(list);
    mu_assert(val == test1, "Wrong value on shift.");
    mu_assert(List_count(list) == 0, "Wrong count after shift.");

    return NULL;
}

static int list_node_value_equals(ListNode *node1, ListNode *node2) {
    if (node1 == NULL && node2 == NULL) {
        return 1; // Both NULL, considered equal
    }
    if (node1 == NULL || node2 == NULL) {
        return 0; // One is NULL, the other is not, not equal
    }
    return strcmp(node1->value, node2->value) == 0;
}

char *test_copy()
{
    List_push(list, test1);
    List_push(list, test2);
    List_push(list, test3);
    List *new_list = List_copy(list);

    mu_assert(new_list != NULL, "Failed to copy list.");
    mu_assert(List_count(new_list) == List_count(list), "Wrong count on copy.");
    mu_assert(list_node_value_equals(new_list->first,list->first), "Wrong first on copy."); // 比较内容
    mu_assert(list_node_value_equals(new_list->last,list->last), "Wrong last on copy.");   // 比较内容
    
    List_pop(list);
    List_pop(list);
    List_pop(list);
    List_clear_destroy(new_list);

    return NULL;
}

char *test_split()
{
    List *left = NULL;
    List *right = NULL;
    List *new_list = List_create();
    List_push(new_list, test1);
    List_push(new_list, test2);
    List_push(new_list, test3);
    List_split(new_list, &left, &right, 1); // 传递指针的地址

    mu_assert(List_count(left) == 1, "Wrong count on split.");
    mu_assert(List_count(right) == 2, "Wrong count on split.");
    mu_assert(List_first(left) == test1, "Wrong first on split.");
    mu_assert(List_last(right) == test3, "Wrong last on split.");
    
    List_destroy(left);
    List_destroy(right);
    
    return NULL;
}

char *test_join()
{
    List *new_list = NULL;
    List *left = List_create();
    List *right = List_create();
    List_push(left, test1);
    List_push(left, test2);
    List_push(right, test3);
    new_list = List_join(left, right);

    mu_assert(List_count(new_list) == 3, "Wrong count on join.");
    mu_assert(List_first(new_list) == test1, "Wrong first on join.");
    mu_assert(List_last(new_list) == test3, "Wrong last on join.");
    mu_assert(left->last->next == right->first, "Wrong join pointers.");
    mu_assert(right->first->prev == left->last, "Wrong join pointers.");

    List_destroy(new_list);

    return NULL;
}

char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_push_pop);
    mu_run_test(test_copy);
    mu_run_test(test_split);
    mu_run_test(test_join);
    mu_run_test(test_unshift);
    mu_run_test(test_remove);
    mu_run_test(test_shift);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);