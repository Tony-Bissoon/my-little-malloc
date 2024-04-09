CC = gcc
CFLAGS = -g -Wall -std=c99 -fsanitize=address -O2

memtest: memtest.o mymalloc.o
	$(CC) $(CFLAGS) memtest.o mymalloc.o -o memtest



memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind


test1: test1.o mymalloc.o
	$(CC) $(CFLAGS) test1.o mymalloc.o -o test1

test2: test2.o mymalloc.o
	$(CC) $(CFLAGS) test2.o mymalloc.o -o test2

test3: test3.o mymalloc.o
	$(CC) $(CFLAGS) test3.o mymalloc.o -o test3

test4: test4.o mymalloc.o
	$(CC) $(CFLAGS) test4.o mymalloc.o -o test4

test5: test5.o mymalloc.o
	$(CC) $(CFLAGS) test5.o mymalloc.o -o test5

test6: test6.o mymalloc.o
	$(CC) $(CFLAGS) test6.o mymalloc.o -o test6

test7: test7.o mymalloc.o
	$(CC) $(CFLAGS) test7.o mymalloc.o -o test7

test8: test8.o mymalloc.o
	$(CC) $(CFLAGS) test8.o mymalloc.o -o test8
clean:
	rm -f mymalloc.o memgrind test1 test2 test3 test4 test5 test6 test7 test8
