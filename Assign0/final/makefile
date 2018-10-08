DOBJS = da.o da-0-0.o integer.o
COBJS = cda.o cda-0-0.o integer.o
SOBJS = stack.o da.o stack-0-0.o integer.o
QOBJS = queue.o cda.o queue-0-0.o integer.o
COPTS = -Wall -Wextra -std=c99

all: da-0-0 cda-0-0 stack-0-0 queue-0-0

test: all
	@echo running da-0-0...
	./da-0-0
	@echo running cda-0-0...
	./cda-0-0
	@echo runnning stack-0-0...
	./stack-0-0
	@echo running queue-0-0...
	./queue-0-0

valgrind-all: all
	valgrind ./da-0-0
	valgrind ./cda-0-0
	valgrind ./stack-0-0
	valgrind ./queue-0-0

valgrind: da-0-0
	valgrind ./da-0-0
	
clean:
	rm -f $(DOBJS) $(COBJS) $(SOBJS) $(QOBJS) da-0-0 cda-0-0 stack-0-0 queue-0-0

#Dynamic array
da-0-0: $(DOBJS)
	gcc $(COPTS) $(DOBJS) -o da-0-0

da-0-0.o: da-0-0.c da.h integer.h
	gcc $(COPTS) -c da-0-0.c

da.o: da.c da.h
	gcc $(COPTS) -c da.c

#Circular dynamic array
cda-0-0: $(COBJS)
	gcc $(COPTS) $(COBJS) -o cda-0-0

cda-0-0.o: cda-0-0.c cda.h integer.h
	gcc $(COPTS) -c cda-0-0.c

cda.o: cda.c cda.h
	gcc $(COPTS) -c cda.c

#Stack
stack-0-0: $(SOBJS)
	gcc $(COPTS) $(SOBJS) -o stack-0-0

stack-0-0.o: stack-0-0.c stack.h da.h integer.h
	gcc $(COPTS) -c stack-0-0.c

stack.o: stack.c stack.h da.h
	gcc $(COPTS) -c stack.c

#Queue
queue-0-0: $(QOBJS)
	gcc $(COPTS) $(QOBJS) -o queue-0-0

queue-0-0.o: queue-0-0.c queue.h cda.h integer.h
	gcc $(COPTS) -c queue-0-0.c

queue.o: queue.c queue.h cda.h
	gcc $(COPTS) -c queue.c

#Integer
integer.o: integer.c integer.h
	gcc $(COPTS) -c integer.c