#include "image.h"
#include "block.h"
#include "free.h"
#include <unistd.h>
#include <stdio.h>

int alloc(void){
    return NULL;
}

unsigned char *bread(int block_num, unsigned char *block) {
    return block;
}

void bwrite(int block_num, unsigned char *block) {
    int byte_offset = block_num * BLOCK_SIZE;
    lseek(image_fd, byte_offset, SEEK_SET);
    write(image_fd, block, BLOCK_SIZE);
}