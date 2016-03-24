#ifndef BLOCKING_H
#define BLOCKING_H

struct message_blocks {

    void** bloks;
    size_t size;
    size_t b_size;
};

extern struct message_blocks* create_message_bloks(size_t m_size, size_t b_size);
extern int init_blocks(const char* m, size_t m_size, struct message_blocks* bloks);
extern void free_blocks(struct message_blocks* b);

extern void print_blocks(struct message_blocks* b);

#endif
