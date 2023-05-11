#ifndef FREE_H
#define FREE_H
#define BLOCK_SIZE 4096
#define INODE_BLOCK 1
#define DATA_BLOCK 2
#define SET_BIT 1

int find_low_clear_bit(unsigned char x);
void set_free(unsigned char *block, int num, int set);
int find_free(unsigned char *block);

#endif