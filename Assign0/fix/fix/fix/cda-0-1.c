#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "integer.h"
#include "real.h"
#include "string.h"
#include "cda.h"

void srandom(unsigned int);
long int random(void);

static void
display(CDA *p,char *intro)
    {
    printf("%s",intro);
    if (sizeCDA(p) < 200)
        {
        displayCDA(p,stdout);
        }
    else
        {
        int k = 100;
        int j;
        printf("(displaying first and last %d elements)\n",k);
        for (j = 0; j < k; ++j)
            {
            displayINTEGER(getCDA(p,j),stdout);
            printf(" ");
            }
        printf("... ");
        for (j = 0; j < k; ++j)
            {
            displayINTEGER(getCDA(p,sizeCDA(p)-k+j),stdout);
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
    printf("REAL test of CDA, simple\n");
    int i;
    CDA *p = newCDA();
    setCDAdisplay(p,displayREAL);
    setCDAfree(p,freeREAL);
    debugCDA(p,1);
    display(p,"items: ");
    for (i = 0; i < 2; ++i)
        {
        insertCDA(p,0,newREAL(3.3));
        insertCDA(p,1,newREAL(2.2));
        insertCDA(p,0,newREAL(4.4));
        insertCDA(p,3+i,newREAL(1.1));
        display(p,"items: ");
        debugCDA(p,0);
        }
    freeREAL(removeCDA(p,1));
    display(p,"items: ");
    freeREAL(removeCDA(p,sizeCDA(p)-1));
    display(p,"items: ");
    freeREAL(removeCDA(p,0));
    display(p,"items: ");
    freeREAL(removeCDA(p,0));
    display(p,"items: ");
    printf("size: %d\n",sizeCDA(p));
    freeCDA(p);
    return 0;
    }
