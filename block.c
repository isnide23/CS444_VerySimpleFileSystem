#include "image.h"
#include "block.h"
#include "free.h"
#include <unistd.h>
#include <stdio.h>

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