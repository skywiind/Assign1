QOBJS = queue.o cda.o
BOBJS = bst.o tnode.o
GOBJS = gst.o bst.o tnode.o
ROBJS = rbt.o gst.o tnode.o
DOBJS = string.o
COPTS = -Wall -Wextra -std=c99

all: trees

test: all
	@echo Testing RBT with test corpus...
	./trees -r corpus commands
	
valgrind-all: all
	valgrind ./trees -g corpus commands
	valgrind ./trees -r corpus commands
	
valgrind: all
	valgrind ./trees -r corpus commands
	
clean:
	rm -f $(QOBJS) $(BOBJS) $(GOBJS) $(ROBJS) $(DOBJS) trees
	
tres: $(ROBJS) $(GOBJS) $(BOBJS) $(QOBJS) $(DOBJS) trees.c
	gcc $(COPTS) $(ROBJS) $(GOBJS) $(BOBJS) $(QOBJS) $(DOBJS) -o trees trees.c

rbt.o: gst rbt.h rbt.c
	gcc $(COPTS) -c rbt.c
	
gst.o: bst gst.h gst.c
	gcc $(COPTS) -c gst.c
	
bst.o: $(QOBJS) bst.h bst.c tnode.o
	gcc $(COPTS) -c bst.c
	
tnode.o: tnode.c tnode.h
	gcc $(COPTS) -c tnode.c
	
queue.o: cda.o queue.c queue.h
	gcc $(COPTS) -c queue.c
	
cda.o: cda.c cda.h
	gcc $(COPTS) -c cda.c
	
string.o: string.c string.h
	gcc $(COPTS) -c string.c
	
scanner.o: scanner.c scanner.h
	gcc $(COPTS) -c scanner.c