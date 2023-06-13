#include "image.h"
#include "block.h"
#include "free.h"
#include "mkfs.h"
#include "ctest.h"
#include "inode.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

void test_image_open(void){
    CTEST_ASSERT(image_open("new_file", 1) != -1, "assert image open succeeds");
    CTEST_ASSERT(image_open("/new_file", 1) == -1, "assert non-file image open fails");
}

void test_image_close(void){
    CTEST_ASSERT(image_close() == -1, "assert image close succeeds");
    image_open("test_file", 1);
    CTEST_ASSERT(image_close() != -1, "assert image close succeeds");
}

void test_bwrite_and_bread(void){

}

void test_find_free(void){

}

void test_set_free(void){
    unsigned char test_block_1[BLOCK_SIZE] = {5};
    unsigned char test_block_2[BLOCK_SIZE] = {5};
    CTEST_ASSERT(memcmp(test_block_1, test_block_2, BLOCK_SIZE) == 0, "assert test blocks match");
}

void test_alloc(void){
    image_open("test_file", TRUNCATE);
    unsigned char block[BLOCK_SIZE];
    mkfs();

    CTEST_ASSERT(alloc() == 7, "next block is 7");
    CTEST_ASSERT(alloc() == 8, "next block is 8");
    memset(block, 255, BLOCK_SIZE);
    bwrite(DATA_BLOCK, block);
    CTEST_ASSERT(alloc() == -1, "all blocks filled");


    image_close();
}

void test_ialloc(void){

}

void test_mkfs(void){
    image_open("test_file", TRUNCATE);
    unsigned char read_block[BLOCK_SIZE];

    mkfs();
   
    int end_of_file = lseek(image_fd, 0, SEEK_END);
    CTEST_ASSERT(end_of_file == 4194304, "assert file size is 4096*1024 = 4194304");
   
    bread(DATA_BLOCK, read_block);
    int free_block_num = find_free(read_block);
    CTEST_ASSERT(free_block_num == 7, "assert 6 blocks reserved on making file system");
}

void test_find_incore_free(void){
    image_open("test_file", TRUNCATE);
    mkfs();
    free_all_incore();
    CTEST_ASSERT(find_incore_free() != NULL, "not equal to NULL");

    alloc_all_incore();
    CTEST_ASSERT(find_incore_free() == NULL, "could not find free inode");

    image_close();
}

void test_read_and_write_inode(void){
    image_open("test_file", TRUNCATE);
    mkfs();
    {
        struct inode in = {
            .inode_num = 0,
            .size = 10,
            .flags = 9,
            .block_ptr = {[15]=8}
        };
        struct inode in_2;
        write_inode(&in);
        read_inode(&in_2, 0);
        CTEST_ASSERT(in.size == in_2.size, "inode size match");
        CTEST_ASSERT(in.flags == in_2.flags, "flags match");
        CTEST_ASSERT(in.block_ptr[15] == in_2.block_ptr[15], "block pointers match");
    }

    {
        struct inode in = {
            .inode_num = 63,
            .size = 10,
            .flags = 9,
            .block_ptr = {[15]=8}
        };
        struct inode in_2;
        write_inode(&in);
        read_inode(&in_2, 63);
        CTEST_ASSERT(in.size == in_2.size, "inode size match");
        CTEST_ASSERT(in.flags == in_2.flags, "flags match");
        CTEST_ASSERT(in.block_ptr[15] == in_2.block_ptr[15], "block pointers match");
    }
    image_close();
}

int main(){

    CTEST_VERBOSE(1);
    test_image_open();
    test_image_close();
    test_mkfs();
    test_alloc();
    test_ialloc();
    test_bwrite_and_bread();
    test_find_free();
    test_set_free();
    test_find_incore_free();
    test_read_and_write_inode();
    CTEST_RESULTS();
    CTEST_EXIT();

    return 0;
}