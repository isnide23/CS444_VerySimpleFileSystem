#include "mkfs.h"
#include "block.h"
#include "image.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void mkfs(void) {
    unsigned char* block[BLOCK_SIZE] = {0};
    for (int i = 0; i < NUM_BLOCKS; i++) {
        write(image_fd, block, BLOCK_SIZE);
    }
    for (int i = 0; i < 7; i++) {
        alloc();
    }
}