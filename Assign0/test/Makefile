#You will need to modify this Makefile, or a copy of yours, to have $(ARG).o
#Below is an example snippet, with an ARG file and a static file, integer.
#You will also need to input the rest of your objects.
OBJS = $(ARG).o integer.o
OPTS = -Wall -Wextra -g -std=c99

assign : $(OBJS)
	gcc $(OPTS) $(OBJS) -o assign -lm
	
assign.o : $(ARG).c integer.h string.h
	gcc $(OPTS) -c $(ARG).c

integer.o : integer.c integer.h
	gcc $(OPTS) -c integer.c

