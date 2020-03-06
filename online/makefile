SOURCE = $(wildcard *.c)
TARGETS = $(patsubst %.c, %, $(SOURCE))

 CC = gcc
 CFLAGS = -Wall -g

all:$(TARGETS)

$(TARGETS):%:%.c head.h
	$(CC) $< $(CFLAGS) -o $@


.PHONY:clean all
clean:
	-rm -rf $(TARGETS)
