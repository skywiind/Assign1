#include <stdio.h>
#include <stdlib.h>
#include "gst.h"
#include "rbt.h"
#include "integer.h"
#include "real.h"
#include "string.h"

void srandom(unsigned int);
long int random(void);

int
main(void)
    {
    srandom(17);
    printf("INTEGER test of RBT, insertions\n");
    int i;
    RBT *p = newRBT(compareINTEGER);
    setRBTdisplay(p,displayINTEGER);
    setRBTfree(p,freeINTEGER);
    for (i = 0; i < 165; ++i)
        {
        int j = random() % 82;
        INTEGER *a = newINTEGER(j);
        insertRBT(p,a);
        }
    if (sizeRBT(p) < 200)
        {
        printf("RBT:\n");
        debugRBT(p,0);
        displayRBT(p,stdout);
        printf("debug (in-order): ");
        displayRBT(p,stdout);
        printf("\n");
        debugRBT(p,2);
        printf("debug (pre-order): ");
        displayRBT(p,stdout);
        printf("\n");
        debugRBT(p,3);
        printf("debug (post-order): ");
        displayRBT(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeRBT(p));
    statisticsRBT(p,stdout);
    setRBTfree(p,freeINTEGER);
    freeRBT(p);
    return 0;
    }
