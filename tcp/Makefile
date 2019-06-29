.PHONY:all
all: client server

CC=gcc

%.o:%.c
	$(CC) -o $@ $<

.PHONY:clean
clean:
	rm -rf client server
