#include "inode.h"
#include "free.h"
#include "image.h"
#include "block.h"
#include <unistd.h>
#include <stdio.h>

// call bread() to get the inode map, then find_free() to 
// locate a free inode, then set_free() to mark it as non-free, 
// then bwrite() to save the inode back out to disk.

int ialloc(void) {
    unsigned char inode_map[BLOCK_SIZE] = {0};
    bread(INODE_MAP_NUM, inode_map);
    int lowest_free = find_free(inode_map);
    set_free(inode_map, lowest_free, SET_BIT);
    bwrite(INODE_MAP_NUM, inode_map);
    return lowest_free;
}