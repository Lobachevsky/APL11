#include "apl.h"

ex_print()
{

   epr0();
   putchar('\n');
}

ex_hprint()
{

   epr0();
   pop();
}

epr0()
{
   register struct item *p;
   register data *dp;
   register i;
   int j;
   int param[4];

   p = fetch1();
   if(p->size == 0)
      return;
   if(p->type == DA) {
      for(i=0; i<4; i++)
         param[i] = 0;
      dp = p->datap;
      for(i=0; i<p->size; i++)
         epr1(*dp++, param);
      i = param[1] + param[2]; /* size if fp */
      if(i > thread.digits)
         i =+ 100;
      if(param[2])
         i++;
      if(i > param[0]+5) {
         i = param[0] + 5; /* size if ep */
         param[1] = param[0];
         param[2] = -1;
      }
      if(param[3])
         i++;   /* sign */
      i++;      /* leading space */
      param[0] = i;
      dp = p->datap;
   }
   bidx(p);
   for(i=1; i<p->size; i++) {
      if(intflg)
         break;
      if(p->type == CH) {
         j = getdat(p);
         putchar(j);
      } else
         epr2(*dp++, param);
      for(j=p->rank-2; j>=0; j--)
         if(i%idx.del[j] == 0)
            putchar('\n');
   }
   if(p->type == CH) {
      j = getdat(p);
      putchar(j);
   } else
      epr2(*dp, param);
}

epr1(d, param)
data d;
int *param;
{
   double f;
   register a;
   register char *c;
   int dp, sg;

   f = d;
   c = ecvt(f, thread.digits, &dp, &sg);
   a = thread.digits;
   while(c[a-1]=='0' && a>1)
      a--;
   if(a > param[0])      /* sig digits */
      param[0] = a;
   a =- dp;
   if(a < 0)
      a = 0;
   if(a > param[2])      /* digits to right of dp */
      param[2] = a;
   if(dp > param[1])      /* digits to left of dp */
      param[1] = dp;
   param[3] =| sg;      /* and sign */
}

epr2(d, param)
int *param;
data d;
{
   register i;
   register char *c, *mc;
   double f;
   int dp, sg;

   if(param[0]+column > thread.width) {
      putchar('\n');
      putto(param[0]);
   }
   f = d;
   c = ecvt(f, thread.digits, &dp, &sg);
   mc = c + thread.digits;
   putchar(' ');
   sg = sg? '"': ' ';
   if(param[2] < 0) {
      if(param[3])
         putchar(sg);
      for(i=0; i<param[1]; i++) {
         putchar(*c++);
         if(i == 0)
            putchar('.');
      }
      putchar('e');
      dp--;
      if(dp < 0) {
         putchar('"');
         dp = -dp;
      } else
         putchar(':');   /* an apl style plus sign */
      putchar(dp/10 + '0');
      putchar(dp%10 + '0');
      return;
   }
   i = dp;
   if(i < 0)
      i = 0;
   for(; i<param[1]; i++)
      putchar(' ');
   if(param[3])
      putchar(sg);
   for(i=0; i<dp; i++)
      if(c >= mc)
         putchar('0'); else
         putchar(*c++);
   for(i=0; i<param[2]; i++) {
      if(i == 0)
         putchar('.');
      if(dp < 0) {
         putchar('0');
         dp++;
      } else
      if(c >= mc)
         putchar('0'); else
         putchar(*c++);
   }
}
