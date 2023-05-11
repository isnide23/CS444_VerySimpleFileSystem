#include "free.h"
#include "image.h"
#include <stdio.h>

int find_low_clear_bit(unsigned char x) {
    for (int i = 0; i < 8; i++)
    if (!(x & (1 << i)))
        return i;
    
    return -1;
}

void set_free(unsigned char *block, int num, int set) {
    int byte_num = num / 8;  
    int bit_num = num % 8;
    if (set == SET_BIT) {
        block[byte_num] |= 1 << bit_num;
    } else {
        block[byte_num] &= ~(1 << bit_num);
    }

}

int find_free(unsigned char *block) {
    int free_bit = -1;
    for (int byte=0; byte < 4096; byte++){
        free_bit = find_low_clear_bit(block[byte]);
        if (free_bit != -1){
            free_bit += (byte * 8);
            break;
        }
    }
    return free_bit;
}