#include "image.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int image_fd;

int image_open(char *filename, int truncate) {
    if (!truncate) {
        image_fd = open(filename, O_RDWR | O_CREAT, 0600);
    } else {
        image_fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0600);
    }
    return image_fd;
}

int image_close(void) {
    int return_value;
    return_value = close(image_fd);
    return return_value;
}