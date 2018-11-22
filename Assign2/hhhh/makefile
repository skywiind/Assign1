OPTS = -Wall -Wextra -std=c99 -g
OBJS = cda.o queue.o bst.o gst.o tnode.o rbt.o $(ARG).o integer.o string.o real.o scanner.o
#assign.o used to be $(ARG).o
all: assign

scanner.o : scanner.c scanner.h
	gcc $(OPTS) -c scanner.c

tnode.o : tnode.c tnode.h
	gcc $(OPTS) -c tnode.c

integer.o : integer.c integer.h
	gcc $(OPTS) -c integer.c

string.o : string.c string.h
	gcc $(OPTS) -c string.c

real.o : real.c real.h
	gcc $(OPTS) -c real.c
	
cda.o : cda.c cda.h
	gcc $(OPTS) -c cda.c
	
queue.o : queue.c queue.h cda.h
	gcc $(OPTS) -c queue.c

bst.o : bst.c bst.h queue.h tnode.h
	gcc $(OPTS) -c bst.c

gst.o : gst.c gst.h bst.h tnode.h
	gcc $(OPTS) -c gst.c

rbt.o : rbt.c rbt.h gst.h tnode.h
	gcc $(OPTS) -c rbt.c
	
$(ARG).o : $(ARG).c rbt.h gst.h bst.h tnode.h cda.h queue.h integer.h string.h real.h scanner.h
	gcc $(OPTS) -c $(ARG).c

assign : $(OBJS)
	gcc $(OPTS) $(OBJS) -o assign

clean :
	rm -f $(OBJS) trees

copy :
	cp ../objects/bst.o .
	cp ../objects/gst.o .
	cp ../objects/rbt.o .
	cp ../objects/tnode.o .

test: trees
	./trees -r t-0-0.corpus debugCommands.txt

test2 : trees
	./trees -g t-0-1.data t-0-1.more

test3 : trees
	./trees -r t-0-1.data t-0-1.more

valgrind2 : trees
	valgrind --leak-check=full ./trees -g t-0-0.corpus t-0-0.commands

valgrind3 : trees
	valgrind --leak-check=full ./trees -r t-0-1.data t-0-1.more

valgrind : trees
	valgrind ./trees -g t-0-1.data t-0-1.more
