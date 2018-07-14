#
# define lex0 257
# define lex1 258
# define lex2 259
# define lex3 260
# define lex4 261
# define lex5 262
# define lex6 263
# define lpar 264
# define rpar 265
# define lbkt 266
# define rbkt 267
# define eol 268
# define unk 269
# define com 270
# define com0 271
# define strng 272
# define null 273
# define dot 274
# define cln 275
# define quad 276
# define semi 277
# define comnt 278
# define tran 279
# define asg 280
# define nam 281
# define numb 282
# define nfun 283
# define mfun 284
# define dfun 285
# define comexpr 286
# define comnam 287
# define comnull 288
# define dscal 289
# define mdscal 290
# define m 291
# define d 292
# define md 293
# define msub 294
# define mdsub 295
#include "apl.h"
   int   vcount;
   int   scount;
   int   litflag;
   int   nlexsym;
   int   context;
   char   *iline;
   char   *ccharp;
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar, yyerrflag;

int yyval 0;
int *yypv;
int yylval 0;
yyactr(__np__){

switch(__np__){

case 1:
   {
      integ = ccharp[-1];
      if(integ != ASGN && integ != PRINT)
         *ccharp++ = PRINT;
      *ccharp++ = EOL;
   } break;
case 2:
   {
      *ccharp++ = IMMED;
      *ccharp++ = yypv[3];
   } break;
case 8:
   {
      switch(context) {

      case lex3:
         name(yyval, AUTO);
         *ccharp++ = ELID;
         break;

      case lex4:
         integ = ccharp;
         *ccharp++ = EOL;
         name(yyval, NAME);
         name(yyval, REST);
         invert(yypv[3], integ);
      }
   } break;
case 9:
   {
      if(context == lex3)
         *ccharp++ = ELID;
   } break;
case 10:
   {
      if(context == lex4)
         invert(yyval, yypv[2]);
   } break;
case 11:
   {
      yyval = ccharp;
      switch(context) {

      case lex2:
         name(yypv[2], DF);
         break;

      case lex3:
         name(yypv[1], ARG1);
         name(yypv[3], ARG2);
         break;

      case lex4:
         name(yypv[1], REST);
         name(yypv[3], REST);
      }
   } break;
case 12:
   {
      yyval = ccharp;
      switch(context) {

      case lex2:
         name(yypv[1], MF);
         break;

      case lex3:
         name(yypv[2], ARG1);
         break;

      case lex4:
         name(yypv[2], REST);
      }
   } break;
case 13:
   {
      if(context == lex2)
         name(yyval, NF);
      yyval = ccharp;
   } break;
case 14:
   {
      yyval = yypv[3];
      switch(context) {

      case lex3:
         name(yypv[2], AUTO);
         break;

      case lex4:
         integ = name(yypv[2], REST);
         invert(yyval, integ);
      }
   } break;
case 15:
   {
      yyval = ccharp;
   } break;
case 16:
   {
      litflag = -1;
   } break;
case 18:
   {
      name(yypv[2], NAME);
   } break;
case 21:
   {
      yyval = ccharp;
      *ccharp++ = BRAN0;
   } break;
case 22:
   {
      yyval = yypv[2];
      *ccharp++ = BRAN;
   } break;
case 24:
   {
      litflag = 1;
      yyval = ccharp;
      *ccharp++ = COMNT;
   } break;
case 28:
   {
      *ccharp++ = PRINT;
   } break;
case 30:
   {
      *ccharp++ = HPRINT;
   } break;
case 32:
   {
      invert(yyval, yypv[2]);
   } break;
case 33:
   {
      invert(yyval, yypv[3]);
   } break;
case 35:
   {
      invert(yyval, yypv[3]);
      *ccharp++ = INDEX;
      *ccharp++ = scount;
      scount = yypv[2];
   } break;
case 36:
   {
      yyval = name(yyval, FUN);
   } break;
case 37:
   {
      yyval = name(yyval, NAME);
   } break;
case 38:
   {
      yyval = ccharp;
      ccharp =+ 2;
      integ = iline[-1];
      vcount = 0;
      for(;;) {
         if(*iline == '\n') {
            nlexsym = unk;
            break;
         }
         if(*iline == integ) {
            iline++;
            break;
         }
         *ccharp++ = *iline++;
         vcount++;
      }
      yyval->c[0] = QUOT;
      yyval->c[1] = vcount;
   } break;
case 39:
   {
      *ccharp++ = CONST;
      *ccharp++ = vcount;
      invert(yyval, ccharp-2);
   } break;
case 40:
   {
      yyval = yypv[2];
   } break;
case 41:
   {
      yyval = ccharp;
      *ccharp++ = yypv[1];
   } break;
case 42:
   {
      vcount++;
   } break;
case 43:
   {
      vcount = 1;
   } break;
case 44:
   {
      yyval = ccharp;
      for(integ=0; integ<SDAT; integ++)
         *ccharp++ = datum.c[integ];
   } break;
case 45:
   {
      yyval = scount;
      scount = 1;
   } break;
case 47:
   {
      invert(yyval, yypv[3]);
      scount++;
   } break;
case 49:
   {
      yyval = ccharp;
      *ccharp++ = ELID;
   } break;
case 50:
   {
      yyval = ccharp;
      *ccharp++ = yypv[1];
   } break;
case 51:
   {
      yyval = yypv[2];
      *ccharp++ = yypv[1]+1;
   } break;
case 52:
   {
      yyval = name(yyval, FUN);
   } break;
case 53:
   {
      yyval = ccharp;
      *ccharp++ = yypv[2]+1;
      *ccharp++ = yypv[1];
   } break;
case 54:
   {
      yyval = yypv[3];
      *ccharp++ = yypv[2]+3;
      *ccharp++ = yypv[1];
   } break;
case 57:
   {
      yyval++;
   } break;
case 59:
   {
      yyval =+ 2;
   } break;
case 60:
   {
      yyval = ccharp;
      *ccharp++ = yypv[1];
   } break;
case 61:
   {
      yyval = yypv[2];
      *ccharp++ = yypv[1];
   } break;
case 62:
   {
      yyval = name(yyval, FUN);
   } break;
case 63:
   {
      yyval = ccharp;
      *ccharp++ = OPROD;
      *ccharp++ = yypv[3];
   } break;
case 64:
   {
      yyval = ccharp;
      *ccharp++ = IPROD;
      *ccharp++ = yypv[1];
      *ccharp++ = yypv[3];
   } break;
case 65:
   {
      yyval =+ 2;
   } break;
case 66:
   {
      yyval = yypv[2];
   } break;
}
}
int yyerrval 256;

#include "tab.c"
#include "lex.c"

int yyact[] {0,4353,8194,4354,8195,4355,8196,4356,8197,4357
,8198,4358,8199,0,4096,16384,0,4360,8218,4361
,8203,4368,8216,4372,8219,4374,8204,4377,8215,4378
,8228,4379,8214,4380,8212,4385,8225,4386,8224,4387
,8220,4389,8227,4390,8221,4391,8223,0,4360,8218
,4368,8216,4372,8219,4374,8204,4377,8215,4378,8228
,4379,8214,4380,8212,4385,8225,4386,8224,4387,8220
,4389,8227,4390,8221,4391,8223,0,4377,8233,4379
,8234,4380,8235,4381,8236,0,4360,8218,4368,8216
,4372,8219,4374,8204,4375,8242,4377,8215,4378,8228
,4379,8214,4380,8212,4385,8225,4386,8224,4387,8220
,4389,8227,4390,8221,4391,8223,0,12289,4382,8244
,4383,8245,4384,8246,0,4364,8247,0,12304,12312
,4373,8249,12313,12314,4366,8261,4367,8259,4369,8254
,4376,8260,4381,8253,4385,8257,4386,8224,4388,8258
,4389,8227,4391,8263,12319,4360,8218,4368,8216,4372
,8219,4377,8215,4378,8228,4379,8214,4380,8212,4385
,8225,4386,8224,4387,8220,4389,8227,4390,8221,4391
,8223,0,4362,8266,12322,12338,4362,8268,0,12340
,4366,8270,4367,8271,0,12324,12325,12326,12327,12329
,12343,4362,12346,12344,12345,4362,12347,12367,4366,12368
,4367,12368,4370,12368,12365,12369,4378,8228,12331,12366
,12332,12291,12292,4376,8274,4377,8233,4379,8234,4380
,8235,4381,8236,12301,12297,12370,12371,12372,12373,4364
,8278,4373,8277,0,12293,12294,12295,12308,4360,8218
,4364,8279,4368,8216,4372,8219,4377,8215,4378,8228
,4379,8214,4380,8212,4385,8225,4386,8224,4387,8220
,4389,8227,4390,8221,4391,8223,0,4364,8281,0
,4377,8233,4379,8234,4380,8235,4381,8236,0,12307
,12311,4360,8218,4368,8216,4372,8219,4377,8215,4378
,8228,4379,8214,4380,8212,4385,8225,4386,8224,4387
,8220,4389,8227,4390,8221,4391,8223,0,12318,12348
,12350,4370,8289,0,4370,8290,0,12357,4370,12369
,12358,12359,12360,12361,4362,12364,12362,12353,4362,12363
,12367,12320,4360,8218,4368,8216,4372,8219,4377,8215
,4378,8228,4379,8214,4380,8212,4385,8225,4386,8224
,4387,8220,4389,8227,4390,8221,4391,8223,12337,12333
,12339,12341,4362,8268,12355,12356,4361,8296,0,12330
,4377,8233,4379,8234,4380,8235,4381,8236,0,4377
,8233,4379,8234,4380,8235,4381,8236,12300,12298,4377
,8300,0,12303,12309,4364,8301,0,12290,12305,12306
,12315,4373,8249,12316,12317,12321,12349,4385,8225,4386
,8303,0,4363,8305,4373,8306,0,12334,12336,4363
,8307,0,12342,12328,12296,4377,8233,4379,8234,4380
,8235,4381,8236,12301,12299,12310,12351,12368,12352,12323
,4360,8218,4368,8216,4372,8219,4377,8215,4378,8228
,4379,8214,4380,8212,4385,8225,4386,8224,4387,8220
,4389,8227,4390,8221,4391,8223,12337,12354,12302,12335
,-1};

int yypact[] {0,1,14,17,48,77,77,77,86,117
,118,125,128,129,130,133,134,155,182,185
,186,189,190,195,196,197,198,155,199,200
,201,204,205,208,215,216,219,220,221,222
,223,234,235,236,237,238,239,244,245,246
,247,248,277,155,280,289,290,291,318,155
,319,186,320,321,324,327,328,331,332,333
,334,337,338,341,342,369,370,155,371,372
,375,376,379,380,389,398,399,402,403,404
,407,408,409,410,411,414,415,416,417,417
,422,427,428,429,432,433,434,435,444,239
,445,446,447,448,449,450,477,478,479,-1};

int yyr1[] {0,1,1,1,1,1,1,1,5,5
,8,9,9,9,10,10,3,4,4,4
,6,6,6,2,12,12,12,13,15,15
,14,11,11,11,16,16,19,19,19,19
,19,19,22,22,23,20,21,21,24,24
,17,17,17,17,17,25,25,25,26,26
,18,18,18,18,18,32,27,29,29,31
,31,31,31,31,31,33,33,30,30,30
,28,28,7,7,7,7,-1};

int yyr2[] {0,2,4,2,2,2,2,2,3,1
,2,3,2,1,3,1,1,2,2,1
,1,2,3,2,1,1,1,3,1,1
,1,1,2,3,1,4,1,1,1,1
,3,1,2,1,1,1,1,3,1,0
,1,2,1,2,3,1,1,1,1,1
,1,2,1,3,3,1,3,1,1,1
,1,1,1,1,1,1,1,1,1,1
,1,1,1,1,1,1,-1};

int yygo[] {0,-1,1,3,37,7,49,-1,8,-1
,9,-1,51,5,46,6,47,-1,38,-1
,48,39,83,53,91,82,106,83,107,106
,83,-1,39,82,105,-1,40,-1,45,108
,116,-1,84,16,72,26,80,50,88,52
,90,56,93,58,95,73,101,76,102,114
,101,-1,13,-1,10,56,94,-1,14,-1
,56,-1,92,-1,15,-1,16,-1,58,-1
,17,-1,73,-1,99,34,81,-1,25,-1
,34,114,117,-1,100,-1,18,-1,19,60
,96,78,103,-1,75,15,63,97,110,98
,112,-1,21,-1,77,15,64,-1,30,-1
,59,-1,60,-1,70,-1};

int yypgo[] {0,1,3,9,11,13,19,21,33,37
,39,43,63,65,69,71,73,75,77,79
,81,83,85,89,91,95,97,99,105,113
,115,119,121,123,-1};

int nterms 41;
int nnonter 33;
int nstate 118;
char *yysterm[] {
"error",
"lex0",
"lex1",
"lex2",
"lex3",
"lex4",
"lex5",
"lex6",
"lpar",
"rpar",
"lbkt",
"rbkt",
"eol",
"unk",
"com",
"com0",
"strng",
"null",
"dot",
"cln",
"quad",
"semi",
"comnt",
"tran",
"asg",
"nam",
"numb",
"nfun",
"mfun",
"dfun",
"comexpr",
"comnam",
"comnull",
"dscal",
"mdscal",
"m",
"d",
"md",
"msub",
"mdsub",
0 };

char *yysnter[] {
"$accept",
"line",
"stat",
"bcomand",
"comand",
"func",
"fstat",
"anyname",
"header",
"args",
"autos",
"expr",
"statement",
"hprint",
"hsemi",
"output",
"e1",
"monadic",
"dyadic",
"e2",
"lsub",
"subs",
"vector",
"number",
"sub",
"monad",
"smonad",
"subr",
"scalar",
"comp",
"mondya",
"dyad",
"sdyad",
"mdcom" };
