#undef NDEBUG
#ifndef _minunit_h
#define _minunit_h

#include <stdio.h>
#include <dbg.h>
#include <stdlib.h>

// 在测试函数的开始部分初始化一个 char *message 变量，该变量用来存储测试过程中可能发生的错误消息。
#define mu_suite_start() char *message = NULL

// 执行测试断言,检查 test 是否为真，如果断言失败，调用 log_err 函数记录错误消息，然后返回错误消息。
#define mu_assert(test, message) if (!(test)) { log_err(message); return message; }

// 运行一个具体的测试函数test，若test() 返回非空消息（即该函数测试失败），则宏返回该消息。
#define mu_run_test(test) debug("\n-----%s", " " #test); \
    message = test(); tests_run++; if (message) return message;

// 定义了main函数，作为测试执行的入口，接受一个测试函数名称name，返回非空消息（即存在函数测试失败），输出执行测试数量。
#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
    argc = 1; \
    debug("----- RUNNING: %s", argv[0]);\
        printf("----\nRUNNING: %s\n", argv[0]);\
        char *result = name();\
        if (result != 0) {\
            printf("FAILED: %s\n", result);\
        }\
        else {\
            printf("ALL TESTS PASSED\n");\
        }\
    printf("Tests run: %d\n", tests_run);\
        exit(result != 0);\
}


// #把紧跟其后的参数用双引号括起来，将其转换为一个字符串； ##将前后两个参数连接起来形成一个新的标识符
int tests_run;

#endif