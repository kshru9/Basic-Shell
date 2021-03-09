CC = gcc

all: dir build

dir:
	@echo "Creating directory..."
	mkdir binaries

build: ls.o mv.o mkdir.o cp.o pwd.o chmod.o rm.o cat.o grep.o
	@echo "Building"
	$(CC) shell.c -o ./binaries/shell

ls.o: ls.c
	@echo "Building ls..."
	$(CC) ls.c -o ./binaries/ls

mv.o: mv.c
	@echo "Building mv..."
	$(CC) mv.c -o ./binaries/mv

mkdir.o: mkdir.c
	@echo "Building mkdir..."
	$(CC) mkdir.c -o ./binaries/mkdir

cp.o: cp.c
	@echo "Building cp..."
	$(CC) cp.c -o ./binaries/cp

pwd.o: pwd.c
	@echo "Building pwd..."
	$(CC) pwd.c -o ./binaries/pwd

chmod.o: chmod.c
	@echo "Building chmod..."
	$(CC) chmod.c -o ./binaries/chmod

rm.o: rm.c
	@echo "Building rm..."
	$(CC) rm.c -o ./binaries/rm

cat.o: cat.c
	@echo "Building cat..."
	$(CC) cat.c -o ./binaries/cat

grep.o: grep.c
	@echo "Building grep..."
	$(CC) grep.c -o ./binaries/grep

clean:
	@echo "Cleaning"
	rm -r binaries
