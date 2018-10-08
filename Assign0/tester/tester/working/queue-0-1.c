#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "cda.h"
#include "queue.h"

void srandom(unsigned int);
long int random(void);

static void
display(QUEUE *p,char *intro)
    {
    printf("%s",intro);
    if (sizeQUEUE(p) < 200)
        {
        displayQUEUE(p,stdout);
        }
    else
        {
        printf("(displaying top element)\n");
        displayINTEGER(peekQUEUE(p),stdout);
        printf("\n");
        }
    printf("\n");
    }

int
main(void)
    {
    srandom(2);
    printf("REAL test of QUEUE, simple\n");
    int i;
    QUEUE *p = newQUEUE();
    setQUEUEdisplay(p,displayREAL);
    setQUEUEfree(p,freeREAL);
    display(p,"items: ");
    for (i = 0; i < 3; ++i)
        {
        enqueue(p,newREAL(3.3));
        enqueue(p,newREAL(2.2));
        enqueue(p,newREAL(4.4));
        enqueue(p,newREAL(1.1));
        debugQUEUE(p,i);
        display(p,"items: ");
        }
    debugQUEUE(p,0);
    freeREAL(dequeue(p));
    display(p,"items: ");
    freeREAL(dequeue(p));
    display(p,"items: ");
    freeREAL(dequeue(p));
    display(p,"items: ");
    freeREAL(dequeue(p));
    display(p,"items: ");
    printf("size: %d\n",sizeQUEUE(p));
    freeQUEUE(p);
    return 0;
    }
