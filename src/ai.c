#include "apl.h"

funedit()
{
   register struct item *p;
   register f, a;

   p = sp[-1];
   if(p->type != LV)
      error("fed B");
   f = fork();
   if(f == 0) {
      for(f=3; f<7; f++)
         close(f);
      f = "/usr/bin/ed";
      execl(f+4, f+9, p->namep, 0);
      execl(f, f+9, p->namep, 0);
      printf("cannot find the editor!\n");
      exit();
   }
   if(f == -1)
      error("try again");
   a = signal(2, 1);
   while(wait(&integ) != f)
      ;
   signal(2, a);
   funload(0);
}

funload(s)
{
   register struct item *p;
   register f;

   p = sp[-1];
   sp--;
   if(p->type != LV)
      error("fnl B");
   f = open(p->namep, 0);
   if(f <= 0)
      error("cannot open");
   switch(s) {
case 0:
      fundef(f);
      return;
case 2:
      clear();
case 1:
      wsload(f);
      putchar('\n');
   }
}

fundef(f)
{
   register a, c;
   struct nlist *np;
   int b[256];

   ifile = f;
   a = rline(0);
   if(a == 0)
      error("fnd eof");
   c = compile(a, 2);
   free(a);
   if(c == 0)
      goto out;
   copy(IN, c+1, &np, 1);
   erase(np);
   np->use = c->c[0];
   fstat(wfile, b);
   np->label = b[5];
   seek(wfile, b[5], 0);
   seek(ifile, 0, 0);
   while((a=read(ifile, b, 512)) > 0)
      write(wfile, b, a);
   write(wfile, "", 1);
out:
   close(ifile);
   ifile = 0;
}

funcomp(np)
struct nlist *np;
{
   register a, c, *p;
   int err, size;

   ifile = dup(wfile);
   seek(ifile, np->label, 0);
   size = 0;
   err = 0;

pass1:
   a = rline(0);
   if(a == 0) {
      if(err)
         goto out;
      p = alloc((size+2)*SINT);
      *p = size;
      size = 0;
      seek(ifile, np->label, 0);
      err++;
      goto pass2;
   }
   c = compile(a, size==0? 3: 5);
   size++;
   free(a);
   if(c == 0) {
      err++;
      goto pass1;
   }
   free(c);
   goto pass1;

pass2:
   a = rline(0);
   if(a == 0)
      goto pass3;
   c = compile(a, size==0? 3: 5);
   size++;
   free(a);
   if(c == 0)
      goto out;
   p[size] = c;
   goto pass2;

pass3:
   seek(ifile, np->label, 0);
   a = rline(0);
   if(a == 0)
      goto out;
   c = compile(a, 4);
   free(a);
   if(c == 0)
      goto out;
   p[size+1] = c;
   if(debug) {
      dump(p[1]);
      dump(c);
   }
   np->itemp = p;
   err = 0;

out:
   close(ifile);
   ifile = 0;
   if(err)
      error("syntax");
}

ex_fun()
{
   struct nlist *np;
   register *p, s;
   int oldflc, oldpcp;

   pcp =+ copy(IN, pcp, &np, 1);
   if(np->itemp == 0)
      funcomp(np);
   p = np->itemp;
   oldflc = funlc;
   oldpcp = pcp;
   funlc = 0;
   s = *p;
loop:
   funlc++;
   execute(p[funlc]);
   if(intflg)
      error("I");
   if(funlc <= 0 || funlc >= s) {
      execute(p[s+1]);
      funlc = oldflc;
      pcp = oldpcp;
      return;
   }
   pop();
   goto loop;
}

ex_arg1()
{
   register struct item *p;
   struct nlist *np;

   pcp =+ copy(IN, pcp, &np, 1);
   p = fetch1();
   sp[-1] = np->itemp;
   np->itemp = p;
   np->use = DA;
}

ex_arg2()
{
   register struct item *p;
   struct nlist *np;

   pcp =+ copy(IN, pcp, &np, 1);
   p = fetch(sp[-2]);
   sp[-2] = np->itemp;
   np->itemp = p;
   np->use = DA;
}

ex_auto()
{
   struct nlist *np;

   pcp =+ copy(IN, pcp, &np, 1);
   *sp++ = np->itemp;
   np->itemp = 0;
   np->use = 0;
}

ex_rest()
{
   register struct item *p;
   struct nlist *np;

   p = fetch1();
   pcp =+ copy(IN, pcp, &np, 1);
   erase(np);
   np->itemp = sp[-2];
   np->use = 0;
   if(np->itemp)
      np->use = DA;
   sp--;
   sp[-1] = p;
}

ex_br0()
{

   funlc = 0;
   ex_elid();
}

ex_br()
{
   register struct item *p;

   p = fetch1();
   if(p->size == 0)
      return;
   if(p->size != 1)
      error("branch C");
   funlc = fix(getdat(p));
}
