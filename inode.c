#include "inode.h"
#include "free.h"
#include "image.h"
#include "block.h"
#include "pack.h"
#include <unistd.h>
#include <stdio.h>

static struct inode incore[MAX_SYS_OPEN_FILES] = {0};

// int ialloc(void) {
//     unsigned char inode_map[BLOCK_SIZE] = {0};
//     bread(INODE_MAP_NUM, inode_map);
//     int lowest_free = find_free(inode_map);
//     set_free(inode_map, lowest_free, SET_BIT);
//     bwrite(INODE_MAP_NUM, inode_map);
//     return lowest_free;
// }

struct inode* ialloc(void) {
    unsigned char inode_map[BLOCK_SIZE] = {0};
    bread(INODE_MAP_NUM, inode_map);

    int lowest_free = find_free(inode_map);
    if (lowest_free == -1) {
        // No free inodes available
        return NULL;
    }

    set_free(inode_map, lowest_free, 1);
    bwrite(INODE_MAP_NUM, inode_map);

    // Get an in-core version of the newly-allocated inode
    struct inode* in = iget(lowest_free);
    if (in == NULL) {
        // Failed to get in-core inode
        return NULL;
    }

    // Initialize the inode fields
    memset(in, 0, sizeof(struct inode));
    in->inode_num = lowest_free;

    // Save the inode to disk
    write_inode(in);

    return in;
}

struct inode *find_incore_free(void) {
    int i;
    for (i = 0; i < INODE_SIZE; i++ ) {
        if (incore[i].ref_count == 0) {
            return &incore[i];
        } 
    }
    return NULL;
}

struct inode *find_incore(unsigned int inode_num) {
    int i;
    for (i = 0; i < INODE_SIZE; i++ ) {
        if (incore[i].inode_num == inode_num) {
            return &incore[i];
        } 
    }
    return NULL;
}

void read_inode(struct inode *in, int inode_num) {
    unsigned char block[BLOCK_SIZE] = {0};
    int block_num = inode_num / INODES_PER_BLOCK + INODE_FIRST_BLOCK;
    int inode_idx = inode_num % INODE_SIZE;
    int block_offset = inode_idx * INODE_SIZE;
    int offset = block + block_offset;

    bread(block_num, block);
    in->size = read_u32(offset);
    in->owner_id = read_u16(offset + 4); // replace inode offsets
    in->permissions = read_u8(offset + 6);
    in->flags = read_u8(offset + 7);
    in->link_count = read_u8(offset + 8);
    int i;
    for (i = 0; i < 16; i++) {
        in->block_ptr[i] = read_u16(offset + 9 + (i * 2));
    }
}

void write_inode(struct inode *in) {
    // Calculate the block and offset within the block where the inode is stored
    unsigned char block[BLOCK_SIZE] = {0};
    int block_num = in->inode_num / (BLOCK_SIZE / INODE_SIZE);
    int inode_idx = in->inode_num % INODE_SIZE;
    int block_offset = inode_idx * INODE_SIZE;
    int offset = block + block_offset;

    write_u32(offset, in->size);
    write_u16(offset + 4, in->owner_id); // replace inode offsets
    write_u8(offset + 6, in->permissions);
    write_u8(offset + 7, in->flags);
    write_u8(offset + 8, in->link_count);
    int i;
    for (i = 0; i < 16; i++) {
        write_u16(offset + 9 + (i * 2), in->block_ptr[i]);
    }

    // Write the updated block back to disk
    bwrite(block_num, in);

}

struct inode *iget(int inode_num) {
    // Check if the inode is already in-core
    struct inode* in = find_incore(inode_num);
    if (in != NULL) {
        // Increment the reference count
        // and return the pointer to the in-core inode
        in->ref_count++;
        return in;
    }

    // Find a free in-core inode space
    in = find_incore_free();
    if (in == NULL) {
        // No free in-core inode slots available
        return NULL;
    }

    // Read the inode data from disk into the in-core inode
    read_inode(in, inode_num);

    // Set the reference count to 1
    in->ref_count = 1;

    // Set the inode number
    in->inode_num = inode_num;

    // Return the pointer to the in-core inode
    return in;
}

void iput(struct inode *in) {
    if (in->ref_count == 0) {
        // The inode is already not in use
        return;
    }

    // Decrement the reference count
    in->ref_count--;

    if (in->ref_count == 0) {
        // Reference count reached zero, save the inode to disk
        write_inode(in);
    }
}
