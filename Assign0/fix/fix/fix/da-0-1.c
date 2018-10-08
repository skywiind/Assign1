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
    srandom(2);
    printf("REAL test of DA, simple\n");
    int i;
    DA *p = newDA();
    setDAdisplay(p,displayREAL);
    setDAfree(p,freeREAL);
    debugDA(p,1);
    display(p,"items: ");
    for (i = 0; i < 2; ++i)
        {
        insertDA(p,0,newREAL(3.3));
        insertDA(p,1,newREAL(2.2));
        insertDA(p,0,newREAL(4.4));
        insertDA(p,sizeDA(p),newREAL(1.1));
        display(p,"items: ");
        freeREAL(removeDA(p,1));
        display(p,"items: ");
        freeREAL(removeDA(p,sizeDA(p)-1));
        display(p,"items: ");
        freeREAL(removeDA(p,0));
        display(p,"items: ");
        freeREAL(removeDA(p,0));
        display(p,"items: ");
        debugDA(p,0);
        }
    printf("size: %d\n",sizeDA(p));
    freeDA(p);
    return 0;
    }
