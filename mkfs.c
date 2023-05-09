#include "mkfs.h"
#include "block.h"
#include "image.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void mkfs(void){
    unsigned char buf[4096] = {0};
    for (int i=0; i<1024; i++){
        write(image_fd, buf, 4096);
    }
    for (int i=0; i<7; i++){
        alloc();
    }
}