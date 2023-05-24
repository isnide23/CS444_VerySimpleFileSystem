#include "image.h"
#include "block.h"
#include "free.h"
#include "mkfs.h"
#include "ctest.h"
#include "inode.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {

    CTEST_VERBOSE(1);

    image_open("test_file", 1);
    image_close();

    return 0;
}