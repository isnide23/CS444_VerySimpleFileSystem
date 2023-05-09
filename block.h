#ifndef BLOCK_H
#define BLOCK_H

int alloc(void);
unsigned char *bread(int block_num, unsigned char *block);
void bwrite(int block_num, unsigned char *block);

#endif