#include "inode.h"
#include "free.h"
#include "image.h"
#include "block.h"
#include <unistd.h>
#include <stdio.h>

int ialloc(void){
    unsigned char inode_map[BLOCK_SIZE] = {0};
    bread(INODE_MAP_NUM, inode_map);
    int lowest_free = find_free(inode_map);
    set_free(inode_map, lowest_free, SET_UNAVAILABLE);
    bwrite(INODE_MAP_NUM, inode_map);
    return lowest_free;
}