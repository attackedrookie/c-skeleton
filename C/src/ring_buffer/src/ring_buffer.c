#undef NDEBUG
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dbg.h"
#include "ring_buffer.h"

RingBuffer *RingBuffer_create(int length)
{
    RingBuffer *buffer = calloc(1, sizeof(RingBuffer));
    check_mem(buffer);
    buffer->length  = length + 1;
    buffer->start = 0;
    buffer->end = 0;
    buffer->buffer = calloc(buffer->length, 1);
    check_mem(buffer->buffer);

    return buffer;

error:
    if (buffer){
        free(buffer);        
    }
    return NULL;
}

void RingBuffer_destroy(RingBuffer *buffer)
{
    if (buffer) {
        free(buffer->buffer);
        free(buffer);
    }
}

int RingBuffer_write(RingBuffer *buffer, char *data, int length)
{
    check(length > 0 && buffer != NULL && data != NULL, "Invalid inputs.");
    check(length <= RingBuffer_available_space(buffer),
            "Not enough space: %d request, %d available",
            RingBuffer_available_data(buffer), length);

    for (int i = 0; i < length; i++)
    {
        *(RingBuffer_ends_at(buffer)) = *(data + i);
        RingBuffer_commit_write(buffer,1);
    }

    return length;
error:
    return -1;
}

int RingBuffer_read(RingBuffer *buffer, char *target, int amount)
{
    check(amount > 0 && buffer != NULL && target != NULL, "Invalid inputs.");
    check_debug(amount <= RingBuffer_available_data(buffer),
            "Not enough in the buffer: has %d, needs %d",
            RingBuffer_available_data(buffer), amount);

    for (int i = 0; i < amount; i++)
    {
        *(target + i) = *(RingBuffer_starts_at(buffer));
        RingBuffer_commit_read(buffer,1);
    }

    return amount;
error:
    return -1;
}

void *RingBuffer_gets(RingBuffer *buffer)
{
    check(buffer != NULL, "Invalid inputs.")

    char *result = NULL;

    if (RingBuffer_empty(buffer))
    {
        result = calloc(1,1);
        check_mem(result);
        *result = '\0';
    }
    else
    {
        int offset = 0;
        int n = RingBuffer_available_data(buffer);
        result = calloc(1,n + 1);

        for (int i = 0; i < n; i++)
        {
            *(result + i) = *(RingBuffer_starts_at(buffer) + offset);
            offset = (offset + 1) % buffer->length; // 使用模运算处理环形缓存结构
        }
        result[n] = '\0';
    }

    return result;

error:
    if (result) free(result);
    return NULL;
}
