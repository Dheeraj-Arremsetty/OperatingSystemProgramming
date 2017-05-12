#include <stdio.h>
#include <errno.h>

extern int errno ;

int main () {

   FILE * pf;
   int errnum;
   pf = fopen ("unexist.txt", "rb");

   if (pf == NULL) {

      errnum = errno;
      perror("Error printed by perror");
   }
   else {

      fclose (pf);
   }
   printf(" errnum = %d",errnum);
   return errnum;
}
