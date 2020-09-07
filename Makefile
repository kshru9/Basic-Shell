CC = gcc

all: build

build: ls.o mv.o mkdir.o cp.o pwd.o chmod.o rm.o cat.o grep.o
	@echo "Building"
	$(CC) shell.c -o shell

ls.o: ls.c
	@echo "Building ls..."
	$(CC) ls.c -o ls

mv.o: mv.c
	@echo "Building mv..."
	$(CC) mv.c -o mv

mkdir.o: mkdir.c
	@echo "Building mkdir..."
	$(CC) mkdir.c -o mkdir

cp.o: cp.c
	@echo "Building cp..."
	$(CC) cp.c -o cp

pwd.o: pwd.c
	@echo "Building pwd..."
	$(CC) pwd.c -o pwd

chmod.o: chmod.c
	@echo "Building chmod..."
	$(CC) chmod.c -o chmod

rm.o: rm.c
	@echo "Building rm..."
	$(CC) rm.c -o rm

cat.o: cat.c
	@echo "Building cat..."
	$(CC) cat.c -o cat

grep.o: grep.c
	@echo "Building grep..."
	$(CC) grep.c -o grep

clean:
	@echo "Cleaning"
	rm ls
	rm shell
	rm mv
	rm cp
	rm pwd
	rm mkdir
	rm chmod
	rm grep
	rm rm
	rm cat
