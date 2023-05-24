#include "image.h"
#include "block.h"
#include "free.h"
#include <unistd.h>
#include <stdio.h>

int alloc(void) {
    unsigned char data_map[BLOCK_SIZE] = {0};
    bread(DATA_BLOCK, data_map);
    int lowest_free = find_free(data_map);
    set_free(data_map, lowest_free, SET_BIT);
    bwrite(DATA_BLOCK, data_map);
    return lowest_free;
}

unsigned char *bread(int block_num, unsigned char *block) {
    int byte_offset = block_num * BLOCK_SIZE;
    lseek(image_fd, byte_offset, SEEK_SET);
    read(image_fd, block, BLOCK_SIZE);
    return block;
}

void bwrite(int block_num, unsigned char *block) {
    int byte_offset = block_num * BLOCK_SIZE;
    lseek(image_fd, byte_offset, SEEK_SET);
    write(image_fd, block, BLOCK_SIZE);
}