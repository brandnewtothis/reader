#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "text.h"
#include "display.h"

#define MAXROWS 5000

int main(int argc, char *argv[]) {
/*
   char *fName=argv[1];   
   char *text[MAXROWS];
   int rows = 0;
   int cols = 0;

   printf("Opening file %s...\n",fName);


   extract_text(fName,text,&rows,&cols);
   closeText(text,&rows);

  
   printf("Finished,,, exiting\n");

*/	
   printf("Hello World\n");
 
   initialize_display();
   display_driver();
   display_exit();

   return 1;

}
