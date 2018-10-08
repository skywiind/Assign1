#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "da.h"

void srandom(unsigned int);
long int random(void);

static void
display(DA *p,char *intro)
    {
    printf("%s",intro);
    if (sizeDA(p) < 200)
        {
        displayDA(p,stdout);
        }
    else
        {
        int k = 100;
        int j;
        printf("(displaying first and last %d elements)\n",k);
        for (j = 0; j < k; ++j)
            {
            displayINTEGER(getDA(p,j),stdout);
            printf(" ");
            }
        printf("... ");
        for (j = 0; j < k; ++j)
            {
            displayINTEGER(getDA(p,sizeDA(p)-k+j),stdout);
            if (j < k - 1) printf(" ");
            }
        printf("\n");
        }
    printf("\n");
    }

int
main(void)
    {
    srandom(19);
    int i,r,rounds=2,size=2118081,dist=10;
    printf("INTEGER test of DA, delete all\n");
    DA *p = newDA();
    setDAdisplay(p,displayINTEGER);
    setDAfree(p,freeINTEGER);
    debugDA(p,1);
    display(p,"items: ");
    for (r = 0; r < rounds; ++r)
        {
        for (i = 0; i < size; ++i)
            {
            int k = sizeDA(p) < dist? sizeDA(p) : sizeDA(p) - random() % dist;
            insertDA(p,k,newINTEGER(i));
            }
        display(p,"items: ");
        printf("size is %d\n",sizeDA(p));
        while (sizeDA(p) - r > 0)
            {
            int k = sizeDA(p) < dist? sizeDA(p) - 1: sizeDA(p) - 1 - random() % dist;
            freeINTEGER(removeDA(p,k));
            }
        insertDA(p,0,newINTEGER(1));
        display(p,"items: ");
        printf("size is %d\n",sizeDA(p));
        }
    freeDA(p);
    return 0;
    }
