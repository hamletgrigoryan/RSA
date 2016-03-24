#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <blocking.h>

struct message_blocks* create_message_bloks(size_t m_size, size_t b_size)
{
    struct message_blocks* b = malloc(sizeof(struct message_blocks));
    b->b_size = b_size;
    b->size = 0;

    if (m_size % b_size == 0) {
        b->size = m_size / b_size;
    } else if (b_size - m_size % b_size < 3) {
        b->size = m_size / b_size + 2;
    } else {
        b->size = m_size / b_size + 1;
    }
    b->bloks = malloc( sizeof(*b->bloks) * b->size);

    size_t i = 0;
    for (; i < b->size; ++i) {
        b->bloks[i] = malloc(b->b_size);
    }

    size_t pading_size = b->size * b_size - m_size;
    i = 0;
    for (; i < pading_size; ++i) {
        char* bl = b->bloks[i / b->b_size];
        bl[i % b->b_size] = ((i == 0 || i == pading_size -1) ? (char)255 : (char)0);
    }
    return b;
}

int init_blocks(const char* m, size_t m_size, struct message_blocks* b)
{
    int i = m_size - 1;
    size_t j = b->size * b->b_size - 1;
    for (; i >= 0; --i, --j) {
        *(((char*) b->bloks[j / b->b_size]) + j % b->b_size) = m[i];
    }
    return 0;
}

void free_blocks(struct message_blocks* b)
{
    size_t i = 0;
    for (; i < b->size; ++i) {
        free(b->bloks[i]);
    }
    free(b->bloks);
    free(b);
}

void print_blocks(struct message_blocks* b)
{
    size_t i = 0;
    for (; i < b->size; ++i) {
        char* bl = b->bloks[i];
        int j = 0;
        printf("bln = %d | ", i);
        for (; j < b->b_size; ++j) {
            printf("%d %c ", bl[j], bl[j]);
        }
        printf("\n");
    }
}
