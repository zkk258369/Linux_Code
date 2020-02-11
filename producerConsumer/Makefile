all:main


main:Producer_Consumer.o queue.o
	gcc -o main Producer_Consumer.o queue.o -lpthread
Producer_Consumer.o:Producer_Consumer.c queue.h
	gcc -o Producer_Consumer.c -lpthread
queue.o:queue.c queue.h
	gcc -o queue.c queue.h
clean:
	rm -rf *.o
