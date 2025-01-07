#include "minunit.h"
#include "../src/ring_buffer.h"
#include <stdio.h>
#include <string.h>

static char *test_create() {
    RingBuffer *buffer = RingBuffer_create(10);
    mu_assert(buffer != NULL, "Failed to create ring buffer.");
    mu_assert(buffer->length == 11, "Wrong buffer length.");
    mu_assert(buffer->start == 0, "Wrong start index.");
    mu_assert(buffer->end == 0, "Wrong end index.");
    RingBuffer_destroy(buffer);
    return NULL;
}

static char *test_write_read() {
    RingBuffer *buffer = RingBuffer_create(5);
    mu_assert(buffer != NULL, "Failed to create ring buffer.");

    char data[] = "hello";
    int len = strlen(data);
    int rc = RingBuffer_write(buffer, data, len);
    mu_assert(rc == len, "Write failed.");
    mu_assert(RingBuffer_available_data(buffer) == len, "available_data error.");

    char target[6] = {0};
    rc = RingBuffer_read(buffer, target, len);
    mu_assert(rc == len, "Read failed.");
    mu_assert(strcmp(target, data) == 0, "Data read incorrectly.");
    mu_assert(RingBuffer_available_data(buffer) == 0, "available_data error.");

    RingBuffer_destroy(buffer);
    return NULL;
}

static char *test_full_empty() {
    RingBuffer *buffer = RingBuffer_create(3);

    mu_assert(buffer != NULL, "Failed to create ring buffer.");

    mu_assert(RingBuffer_empty(buffer) == 1, "Should be empty at start.");
    mu_assert(RingBuffer_full(buffer) == 0, "Should not be full at start.");

    char data[] = "abc";
    RingBuffer_write(buffer, data, 3);

    mu_assert(RingBuffer_full(buffer) == 1, "Should be full after writing 3 bytes.");
    mu_assert(RingBuffer_empty(buffer) == 0, "Should not be empty after writing.");

    char target[4] = {0};
    RingBuffer_read(buffer, target, 3);
    mu_assert(RingBuffer_empty(buffer) == 1, "Should be empty after reading.");
    mu_assert(RingBuffer_full(buffer) == 0, "Should not be full after reading.");
    RingBuffer_destroy(buffer);
    return NULL;
}

static char *test_wrap_around() {
    RingBuffer *buffer = RingBuffer_create(4);
    mu_assert(buffer != NULL, "Failed to create ring buffer.");

    char data1[] = "abc";
    RingBuffer_write(buffer, data1, 3);

    char target1[4] = {0};
    RingBuffer_read(buffer, target1, 2);
    mu_assert(strcmp(target1, "ab") == 0, "First read failed.");

    char data2[] = "de";
    RingBuffer_write(buffer, data2, 2);

    char target2[4] = {0};
    RingBuffer_read(buffer, target2, 3);
    mu_assert(strcmp(target2, "cde") == 0, "Wrap around read failed.");

    RingBuffer_destroy(buffer);
    return NULL;
}

static char *test_gets()
{
    RingBuffer *buffer = RingBuffer_create(5);
    mu_assert(buffer != NULL, "Failed to create ring buffer.");

    char data[] = "hello";
    int len = strlen(data);
    int rc = RingBuffer_write(buffer, data, len);
    mu_assert(rc == len, "Write failed.");

    char *result = RingBuffer_gets(buffer);
    mu_assert(strcmp(result, data) == 0, "gets failed");
    free(result);

    mu_assert(RingBuffer_empty(buffer) == 0, "buffer shouldn't be empty after gets");
    RingBuffer_destroy(buffer);
    return NULL;
}

static char *test_gets_empty()
{
    RingBuffer *buffer = RingBuffer_create(5);
    mu_assert(buffer != NULL, "Failed to create ring buffer.");
    char *result = RingBuffer_gets(buffer);
    mu_assert(strcmp(result, "") == 0, "gets empty failed");
    free(result);
    RingBuffer_destroy(buffer);
    return NULL;
}

static char *all_tests() {
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_write_read);
    mu_run_test(test_full_empty);
    mu_run_test(test_wrap_around);
    mu_run_test(test_gets);
    mu_run_test(test_gets_empty);

    return NULL;
}

RUN_TESTS(all_tests);