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
    srandom(4);
    int i,r,rounds=2,size=131;
    printf("INTEGER test of STACK, insertions at the front\n");
    STACK *p = newSTACK();
    setSTACKdisplay(p,displayINTEGER);
    setSTACKfree(p,freeINTEGER);
    debugSTACK(p,1);
    display(p,"items: ");
    for (r = 0; r < rounds; ++r)
        {
        for (i = 0; i < size; ++i)
            {
            int j = random() % size;
            push(p,newINTEGER(j));
            }
        display(p,"items: ");
        printf("size is %d\n",sizeSTACK(p));
        }
    freeSTACK(p);
    return 0;
    }
