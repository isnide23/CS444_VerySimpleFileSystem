#ifndef FREE_H
#define FREE_H

#define INODE_MAP_NUM 1

int find_low_clear_bit(unsigned char x);
void set_free(unsigned char *block, int num, int set);
int find_free(unsigned char *block);

#endif