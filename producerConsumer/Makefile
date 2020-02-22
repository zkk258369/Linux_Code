obj = Producer_Consumer.o queue.o
main : $(obj)
	gcc -o main $(obj) -lpthread

Producer_Consumer.o : Producer_Consumer.c queue.h
	gcc -c Producer_Consumer.c -lpthread
queue.o : queue.c queue.h
	gcc -c queue.c 
clean:
	rm $(obj)
