#include "apl.h"

clear()
{
   register struct nlist *n;
   extern freelist[], end;

   for(n=nlist; n->namep; n++) {
      n->itemp = n->use = 0;
      n->namep = 0;
      }
      freelist[0] = 0;
      freelist[1] = -1;   /*empty free list*/
      brk(&end);   /*shrink core*/
}

lsize(s)
char *s;
{
   register i;
   register char *p;

   i=1;
   p=s;
   while (*p++) i++;
   return(i);
}

isize(ip)
struct item *ip;
{
   register struct item *p;
   register i;

   p=ip;
   i=sizeof *p + p->rank*SINT;
   if(p->type == DA)
      i =+ p->size*SDAT; else
   if(p->type == CH)
      i =+ p->size;
   return(i);
}

wsload(ffile)
{
   int b[18];
   char name[NAMS];
   int iz;
   register i;
   register struct nlist *n;
   register struct item *p;
   char c;
   struct {
      int word;
   };

   iz = 0;
/* Check for correct magic number */
   read(ffile,&iz,2);
   if(iz != MAGIC) {
barf:
      close(ffile);
      error("bad load format");
   }
   read(ffile,&thread,sizeof thread);
   while(read(ffile,&iz,2) == 2) {
      i = iz.c[1];
/* read name of vbl or fn */
      read(ffile,name,i);
      for(n=nlist; n->namep; n++)
         if(equal(name,n->namep)) {
            erase(n);
            goto hokay;
         }
      n->namep = alloc(i);
      copy(CH,name,n->namep,i);
hokay:
      n->use = iz.c[0];
      n->type = LV;
      switch(n->use) {
default:
         goto barf;

case DA:
         read(ffile,&iz,2);
         p=alloc(iz);
         read(ffile,p,iz);
         p->label =+  (&p)->word; /*make absolute*/
         n->itemp = p;
         continue;
case NF:
case MF:
case DF:
         n->itemp = 0;
         fstat(wfile,b);
         n->label=b[5];
         seek(wfile,b[5],0);
         do {
            read(ffile,&c,1);
            write(wfile,&c,1);
         } while(c != 0);
      }
   }
   fdat(ffile);
   close(ffile);
}

wssave(ffile)
{
   int iz;
   int jfile;
   register struct nlist *n;
   register i;
   register struct item *p;
   char c;
   struct {
      int word;
   };

   jfile=dup(wfile);
   iz = MAGIC;
   write(ffile,&iz,2);
   write(ffile,&thread,sizeof thread);

   for(n=nlist; n->namep; n++) {
      if(n->use == 0 || (n->use == DA && n->itemp == 0))
         continue;
      iz.c[0] = n->use;
      iz.c[1] = i = lsize(n->namep);
      write(ffile,&iz,2);
      write(ffile,n->namep,i);

      switch(n->use) {
default:
         close(ffile);
         close(jfile);
         error("save B");
case DA:
         p = n->itemp;
         iz = i = isize(p);
         p -> label =- (&p)->word;
         write(ffile,&iz,2);
         write(ffile,p,i);
         p->label =+ (&p)->word;
         continue;
case NF:
case MF:
case DF:
         seek(jfile,n->label,0);
         do {
            read(jfile,&c,1);
            write(ffile,&c,1);
         } while(c != 0);
      }
   }
   fdat(ffile);
   close(ffile);
   close(jfile);
}

listdir()
{
   register f;
   struct {
   int in;
   char nam[14];
   } dir;

   if((f = open(".",0)) < 0)
      error("directory B");
   while(read(f,&dir,sizeof dir) == sizeof dir)
      if(dir.in != 0 && dir.nam[0] != '.') {
         if(column+10 >= thread.width)
            printf("\n\t");
         printf(dir.nam);
         putchar('\t');
      }
   putchar('\n');
   close(f);
}

fdat(f)
{
   int b[18];
   register *p;

   fstat(f,b);
   p = localtime(&b[16]);

   printf("  ");
   pr2d(p[2]);
   putchar('.');
   pr2d(p[1]);
   putchar('.');
   pr2d(p[0]);
   putchar(' ');
   pr2d(p[4]+1);
   putchar('/');
   pr2d(p[3]);
   putchar('/');
   pr2d(p[5]);
}

pr2d(i)
{
   putchar(i/10+'0');
   putchar(i % 10 + '0');
}
