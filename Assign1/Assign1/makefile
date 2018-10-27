COPTS = -Wall -Wextra -std=c99
SOBJS = stack.o da.o
QOBJS = queue.o cda.o
MOBJS = maze.o cell.o

all: amaze

test: all
	@echo testing maze...
	./amaze -c 10 10 m -d m -r 2
	./amaze -s m m -d m

valgrind: all
	valgrind ./amaze -c 10 10 m
	
clean:
	rm -f $(QOBJS) $(SOBJS) $(MOBJS) amaze.o amaze m
	
amaze: $(QOBJS) $(SOBJS) $(MOBJS) amaze.c
	gcc $(COPTS) $(QOBJS) $(MOBJS) $(SOBJS) -o amaze amaze.c
	
maze.o: maze.c maze.h cell.h stack.h queue.h
	gcc $(COPTS) -c maze.c

cell.o: cell.c cell.h
	gcc $(COPTS) -c cell.c
	
da.o: da.c da.h
	gcc $(COPTS) -c da.c
	
cda.o: cda.c cda.h
	gcc $(COPTS) -c cda.c
	
stack.o: stack.c stack.h da.h
	gcc $(COPTS) -c stack.c
	
queue.o: queue.c queue.h cda.h
	gcc $(COPTS) -c queue.c