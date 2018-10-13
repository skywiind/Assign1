SOBJS = da.o stack.o
QOBJS = cda.o queue.o
MOBJS = amaze.o maze.o cell.o
COPTS = -Wall -Wextra -std=c99

all: amaze

test: all
	@echo creating test maze...
	./amaze -c 10 10 m -r 2
	@echo solving  test maze...
	./amaze -s m m
	@echo drawing  test maze...
	./amaze -d m
	
valgrind: all
	valgrind ./amaze -c 10 10 m -r 2
	
clean:
	rm -f $(SOBJS) $(QOBJS) $(MOBJS) amaze
	
amaze: $(MOBJS) $(SOBJS) $(QOBJS)
	gcc $(COPTS) $(MOBJS) $(SOBJS) $(QOBJS) -o amaze
	
da.o: da.c da.h
	gcc $(COPTS) -c da.c
	
cda.o: cda.c cda.h
	gcc $(COPTS) -c cda.c
	
stack.o: stack.c stack.h da.h
	gcc $(COPTS) -c stack.c
	
queue.o: queue.c queue.h cda.h
	gcc $(COPTS) -c queue.c
	
maze.o: maze.c cell.c maze.h cell.h $(SOBJS $(QOBJS)
	gcc $(COPTS) -c maze.c