   #include <stdio.h>
   #include <stdlib.h>
   #include "CDA.h"
   #include "integer.h"
   
   static void showItems(CDA *items)
       {
       printf("The items are ");
       displayCDA(items,stdout);
       printf(".\n");
       printf("The items (debugged) are ");
       debugCDA(items, 1);
	   displayCDA(items, stdout);
	   debugCDA(items, 0);
       printf(".\n");
       }

   int main(int argc, char **argv) {
	   int loop = atoi(argv[1]);
	   srand(loop);
       CDA *items = newCDA();
	   setCDAdisplay(items, displayINTEGER);
	   setCDAfree(items, freeINTEGER);
       showItems(items);
	   for (int i = 0; i < loop; i++) {
		   printf("\n%d", i);
		   insertCDA(items, (rand() % loop), newINTEGER(3));
	   }
       showItems(items);
       printf("The value ");
       INTEGER *i = removeCDA(items,0);                   //remove from front
       displayINTEGER(i,stdout);
       printf(" was removed.\n");
       freeINTEGER(i);
       showItems(items);
       int x = getINTEGER((INTEGER *) getCDA(items,0));    //get the first item
       printf("The first item is %d.\n",x);
       printf("Freeing the list.\n");
       freeCDA(items);
       return 0;
	}