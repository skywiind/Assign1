#include <stdio.h>
#include <stdlib.h>
#include "bst.h"
#include "gst.h"
#include "integer.h"
#include "real.h"
#include "string.h"

void srandom(unsigned int);
long int random(void);

int
main(void)
    {
    srandom(18);
    printf("INTEGER test of GST, insertions, then deletions\n");
    int i;
    GST *p = newGST(compareINTEGER);
    setGSTdisplay(p,displayINTEGER);
    setGSTfree(p,freeINTEGER);
    for (i = 0; i < 198; ++i)
        {
        int j = random() % 99;
        INTEGER *a = newINTEGER(j);
        insertGST(p,a);
        }
    if (sizeGST(p) < 200)
        {
        debugGST(p,0);
        printf("GST:\n");
        displayGST(p,stdout);
        debugGST(p,1);
        printf("debug (in-order): ");
        displayGST(p,stdout);
        printf("\n");
        debugGST(p,2);
        printf("debug (pre-order): ");
        displayGST(p,stdout);
        printf("\n");
        debugGST(p,3);
        printf("debug (post-order): ");
        displayGST(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeGST(p));
    statisticsGST(p,stdout);
    for (i = 0; i < 198; ++i)
        {
        int j = random() % 99;
        INTEGER *a = newINTEGER(j);
        if (freqGST(p,a) > 1)
            deleteGST(p,a);
        else
            {
            INTEGER *x = findGST(p,a);
            setGSTfree(p,0);
            deleteGST(p,a);
            setGSTfree(p,freeINTEGER);
            freeINTEGER(x);
            }
        freeINTEGER(a);
        }
    if (sizeGST(p) < 200)
        {
        debugGST(p,0);
        printf("GST:\n");
        displayGST(p,stdout);
        debugGST(p,1);
        printf("debug (in-order): ");
        displayGST(p,stdout);
        printf("\n");
        debugGST(p,2);
        printf("debug (pre-order): ");
        displayGST(p,stdout);
        printf("\n");
        debugGST(p,3);
        printf("debug (post-order): ");
        displayGST(p,stdout);
        printf("\n");
        }
    printf("size is %d\n",sizeGST(p));
    statisticsGST(p,stdout);
    setGSTfree(p,freeINTEGER);
    freeGST(p);
    return 0;
    }
