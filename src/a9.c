#include "apl.h"

data scalex;
data scaley;

data origx;
data origy;

ex_dibm()
{
   register struct item *p;
   register data *dp;

   register inde;

   inde = topfix();
   p = fetch1();
   if (p->type != DA)
      error("dibm T");
   if (p->size != 4)
      error("dibm C");
   dp = p->datap;
   switch(inde) {
case 1:
      origx = dp[0];
      origy = dp[1];
      scalex = 453./(dp[2] - dp[0]);
      scaley = 453./(dp[3] - dp[1]);
      return;

default:
      error("dibm unk");
   }
}

ex_mibm()
{
   register *p;
   int t[6];

   switch(topfix()) {

   default:
      error("ib unk");

   case 1:
      /* sclr(); */
      datum = 0;
      break;

   case 20: /* time of day */
      time(t);
      p = t;
      goto tod;

   case 21: /* CPU time */
      times(t);
      t[3] = t[0];
      t[0] = 0;
      t[2] = 0;
      datum = ltod(t) + ltod(t+2);
      break;

   case 24: /* starting time */
      p = stime;

   tod:
      p = localtime(p);
      datum = 60.*(p[0]+60.*(p[1]+60.*p[2]));
      break;

   case 25: /* date */
      time(t);
      p = t;
      goto dt;

   /*
    * non standard I functions
    */

   case 28: /* starting date */
      p = stime;

   dt:
      p = localtime(p);
      datum = p[5]+100.*(p[3]+100.*(p[4]+1));
      break;

   case 29: /* iorg */
      datum = thread.iorg;
      break;

   case 30: /* width */
      datum = thread.width;
      break;

   case 31: /* digits */
      datum = thread.digits;
      break;
   }
   p = newdat(DA, 0, 1);
   p->datap[0] = datum;
   *sp++ = p;
}
