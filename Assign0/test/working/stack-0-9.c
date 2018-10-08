#include <stdio.h>
#include <stdlib.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "da.h"
#include "stack.h"

void srandom(unsigned int);
long int random(void);

static void
display(STACK *p,char *intro)
    {
    printf("%s",intro);
    if (sizeSTACK(p) < 200)
        {
        displaySTACK(p,stdout);
        }
    else
        {
        printf("(displaying top element)\n");
        displayINTEGER(peekSTACK(p),stdout);
        printf("\n");
        }
    printf("\n");
    }

int
main(void)
    {
    srandom(10);
    int i,r,rounds=3,size=2075633;
    printf("INTEGER test of STACK, insertions and deletions at front\n");
    STACK *p = newSTACK();
    setSTACKdisplay(p,displayINTEGER);
    setSTACKfree(p,freeINTEGER);
    debugSTACK(p,0);
    display(p,"items: ");
    for (r = 0; r < rounds; ++r)
        {
        for (i = 0; i < size; ++i)
            {
            int j = random() % size;
            push(p,newINTEGER(j));
            }
        int limit = r == rounds - 1? size - random() % size / 2 : 0;
        while (sizeSTACK(p) > limit)
            {
            freeINTEGER(pop(p));
            }
        debugSTACK(p,r);
        display(p,"items: ");
        printf("size is %d\n",sizeSTACK(p));
        }
    freeSTACK(p);
    return 0;
    }
