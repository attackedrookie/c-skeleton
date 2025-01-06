#include "minunit.h"
#include "../src/list_algos.h"
#include <assert.h>
#include <time.h>
#include <string.h>
#include <windows.h>


char *random_list(List *list,int length)
{

    if (length <= 0) {
        return NULL; 
    }

    char *str = malloc(length);
    if (str == NULL) {
        perror("malloc failed");
        return NULL; 
    }

    // 初始化随机数生成器
    static int seeded = 0;
    if (!seeded) {
        srand(time(NULL));
        seeded = 1;
    }

    for (int i = 0; i < length; i++) {
        int rondom_num = rand() % (100 -0 + 1) + 0;
        char *value = malloc(1);
        sprintf(value,"%d",rondom_num);
        str[i] = rondom_num;

        List_push(list,value);
    }

    return str;
}


void display(List *list)
{
    ListNode *node = list->first->next;
    while (node->next) {
        printf("%d  ", atoi(node->value));
        node = node->next;
    }
    printf("\n");
}

char *test_bubble_sort()
{
    int n = 10000;
    
    List *list = List_create();
    char *str = random_list(list,n);
    mu_assert(List_count(list) == n, "list push failed.");

    printf("Before Bubble sorting:\n");
    // for (int i = 0; i < n; i++) {
    //     printf("%d  ", str[i]); // 逐个打印字符
    // }
    // printf("\n");

    List_push(list, "1012");
    List_push(list, "-1");

    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock(); // 记录开始时间
    List_bubble_sort(list, ascending_order); // 升序排序
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU 时间：%.6f 秒\n", cpu_time_used);

    mu_assert(strcmp(List_first(list), "-1") == 0, "Bubble sort failed.");
    mu_assert(strcmp(List_last(list), "1012") == 0, "Bubble sort failed.");

    printf("After Bubble sorting:\n");
    // display(list);

    List_bubble_sort(list, descending_order); // 降序排序

    mu_assert(strcmp(List_first(list), "1012") == 0, "Bubble sort failed.");
    mu_assert(strcmp(List_last(list), "-1") == 0, "Bubble sort failed.");

    // display(list);
    List_destroy(list);
    free(str);

    return NULL;
}

char *test_merge_sort()
{
    
    int n = 10000;
    
    List *list = List_create();
    char *str = random_list(list,n);
    mu_assert(List_count(list) == n, "list push failed.");

    printf("Before Merge sorting:\n");
    // for (int i = 0; i < n; i++) {
    //     printf("%d  ", *(str + i)); // 逐个打印字符
    // }
    // printf("\n");

    List_push(list, "1012");
    List_push(list, "-1");

    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock(); // 记录开始时间
    List_merge_sort(list, ascending_order); // 升序排序
    end_time = clock();
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("CPU 时间：%.6f 秒\n", cpu_time_used);

    mu_assert(strcmp(List_first(list), "-1") == 0, "Merge sort failed.");
    mu_assert(strcmp(List_last(list), "1012") == 0, "Merge sort failed.");

    printf("After Merge sorting:\n");
    // display(list);

    List_merge_sort(list, descending_order); // 降序排序

    mu_assert(strcmp(List_first(list), "1012") == 0, "Merge sort failed.");
    mu_assert(strcmp(List_last(list), "-1") == 0, "Merge sort failed.");

    // display(list);

    List_destroy(list);
    free(str);

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    SetConsoleOutputCP(65001); // 设置控制台代码页为 UTF-8

    mu_run_test(test_bubble_sort);
    mu_run_test(test_merge_sort);

    return NULL;
}

RUN_TESTS(all_tests);