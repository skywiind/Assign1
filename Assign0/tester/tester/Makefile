OBJS = $(ARG).o integer.o da.o cda.o stack.o queue.o
# real.o string.o
OPTS = -Wall -Wextra -g -std=c99

assign0 : $(OBJS)
	gcc $(OPTS) $(OBJS) -o assign0 -lm

assign0.o : $(ARG).c da.h integer.h cda.h stack.h queue.h
	gcc $(OPTS) -c $(ARG).c

da.o : da.c da.h
	gcc $(OPTS) -c da.c
	
cda.o : cda.c cda.h
	gcc $(OPTS) -c cda.c
	
stack.o : stack.c stack.h da.h
	gcc $(OPTS) -c stack.c
	
queue.o : queue.c queue.h cda.h
	gcc $(OPTS) -c queue.c

integer.o : integer.c integer.h
	gcc $(OPTS) -c integer.c
	
#string.o : string.c string.h
#	gcc $(OPTS) -c string.c
	
#real.o : real.c real.h
#	gcc $(OPTS) -c real.c

clean :
	rm -f $(OBJS) assign0 

test :
	assign0
