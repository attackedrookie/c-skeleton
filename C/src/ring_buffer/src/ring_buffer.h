#ifndef _ring_buffer_h
#define _ring_buffer_h



typedef struct {
    char *buffer; // 
    int length; // 缓冲区空间大小
    int start; // 读指针位
    int end; // 写指针位
} RingBuffer;


RingBuffer *RingBuffer_create(int length);

void RingBuffer_destroy(RingBuffer *buffer);

int RingBuffer_read(RingBuffer *buffer, char *target, int amount);

int RingBuffer_write(RingBuffer *buffer, char *data, int length);

void *RingBuffer_gets(RingBuffer *buffer);

#define RingBuffer_available_data(B) (((B)->end - (B)->start + (B)->length) % (B)->length) 

#define RingBuffer_available_space(B) ((B)->length - RingBuffer_available_data(B) - 1)

#define RingBuffer_full(B) (RingBuffer_available_data((B)) + 1 == (B)->length)

#define RingBuffer_empty(B) (RingBuffer_available_data((B)) == 0)

#define RingBuffer_puts(B, D) RingBuffer_write((B), bdata((D)), blength((D)))

#define RingBuffer_get_all(B) RingBuffer_gets((B), RingBuffer_available_data((B)))

#define RingBuffer_starts_at(B) ((B)->buffer + (B)->start)

#define RingBuffer_ends_at(B) ((B)->buffer + (B)->end)

#define RingBuffer_commit_read(B, A) ((B)->start = ((B)->start + (A)) % (B)->length) //将读指针向前移动A个位置。

#define RingBuffer_commit_write(B, A) ((B)->end = ((B)->end + (A)) % (B)->length) // 将写指针向前移动A个位置。 

#endif