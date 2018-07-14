#include "apl.h"

ex_immed()
{
   register i;
   register struct item *p;
   register struct nlist *n;
   double f;

   i = *pcp++;
   switch(i) {

   default:
      error("immed B");

   case DEBUG:
      debug = ~debug;
      return;

   case DIGITS:
      i = topfix();
      if(i < 1 || i > 20)
         error("digits D");
      printf("was %d\n",thread.digits);
      thread.digits = i;
      return;

   case EDIT:
      funedit();
      return;

   case FUZZ:
      i = topfix();
      if(i <= 0) {
         thread.fuzz = 0.;
         return;
      }
      f = i;
      thread.fuzz = exp(-f*2.3025851);
      return;

   case ORIGIN:
      printf("was %d\n",thread.iorg);
      thread.iorg = topfix();
      return;

   case WIDTH:
      i = topfix();
      if(i < 1)
         error("width D");
      printf("was %d\n",thread.width);
      thread.width = i;
      return;

   case READ:
      funload(0);
      return;

   case ERASE:
      p = sp[-1];
      sp--;
      erase(p);
      return;

   case CONTIN:
      if((i=creat("continue",0644)) < 0)
         error("cannot create");
      wssave(i);
      printf(" continue");

   case OFF:
      term();

   case VARS:
      for(n=nlist; n->namep; n++)
         if(n->itemp && n->use == DA) {
            if(column+8 >= thread.width)
               printf("\n\t");
            printf(n->namep);
            putchar('\t');
         }
      putchar('\n');
      return;

   case FNS:
      for(n=nlist; n->namep; n++)
         if(n->use == DF || n->use == MF || n->use == NF) {
            if(column+8 >= thread.width)
               printf("\n\t");
            printf(n->namep);
            putchar('\t');
         }
      putchar('\n');
      return;

   case CLEAR:
      clear();
      printf("clear ws\n");
      break;

   case LIB:
      listdir();
      return;

   case LOAD:
      funload(2);
      break;

   case COPY:
      funload(1);
      return;

   case DROPC:
      i = 1;
      goto drcom;

   case SAVE:
      i = 0;
drcom:
      n = sp[-1];
      sp--;
      if(n->type != LV)
         error("save B");
      if(i) {
         unlink(n->namep);
         return;
      }
      i = creat(n->namep,0644);
      if(i < 0)
         error("cannot create");
      wssave(i);
      putchar('\n');
      return;
   }
   /* special return for after clear */
   sp = stack;
   reset();
}
