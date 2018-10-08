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
    srandom(11);
    int i,r,rounds=2,size=1250;
    printf("INTEGER test of DA, random insertions and deletions\n");
    DA *p = newDA();
    setDAdisplay(p,displayINTEGER);
    setDAfree(p,freeINTEGER);
    debugDA(p,1);
    display(p,"items: ");
    for (r = 0; r < rounds; ++r)
        {
        for (i = 0; i < size; ++i)
            {
            int j = random() % size;
            int k = random() % (sizeDA(p) + 1);
            insertDA(p,k,newINTEGER(j));
            }
        for (i = 0; i < size - random() % size / 2; ++i)
            {
            int k = random() % sizeDA(p);
            freeINTEGER(removeDA(p,k));
            }
        display(p,"items: ");
        printf("size is %d\n",sizeDA(p));
        }
    freeDA(p);
    return 0;
    }
