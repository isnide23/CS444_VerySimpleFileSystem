#include "inode.h"
#include "free.h"
#include "image.h"
#include "block.h"
#include <unistd.h>
#include <stdio.h>

static struct inode incore[MAX_SYS_OPEN_FILES] = {0};

int ialloc(void) {
    unsigned char inode_map[BLOCK_SIZE] = {0};
    bread(INODE_MAP_NUM, inode_map);
    int lowest_free = find_free(inode_map);
    set_free(inode_map, lowest_free, SET_BIT);
    bwrite(INODE_MAP_NUM, inode_map);
    return lowest_free;
}

struct inode *find_incore_free(void) {
    return -1;
}

struct inode *find_incore(unsigned int inode_num) {
    return -1;
}

struct inode *iget(int inode_num) {
    return -1;
}

void iput(struct inode *in) {
    return -1;
}



