block.o: block.c
	gcc -Wall -Wextra -c $<

free.o: free.c
	gcc -Wall -Wextra -c $<

image.o: image.c
	gcc -Wall -Wextra -c $<

inode.o: inode.c
	gcc -Wall -Wextra -c $<

mkfs.o: mkfs.c
	gcc -Wall -Wextra -c $<

simfs_test.o: simfs_test.c
	gcc -Wall -Wextra -c $<

simfs.a: block.o free.o image.o inode.o mkfs.o 
	ar rcs $@ $^

simfs_test: simfs_test.c simfs.a
    gcc -Wall -Wextra -o $@ $^

.PHONY: test

test: simfs_test
    ./simfs_test