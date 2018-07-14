/*
 * Magic Numbers
 */

#define MRANK   8
#define CANBS   300
#define STKS   20
#define NLS   100
#define NAMS   20
#define OBJS   500
#define MAXLAB   30
#define MAGIC   0100554
#define data   double

/*
 * derrived constants
 */

#define   SDAT   sizeof datum
#define   SINT   sizeof integ

/*
 * Interpreter Op Codes
 */

#define EOF   (-1)
#define EOL   0

#define ADD   1
#define PLUS   2
#define SUB   3
#define MINUS   4
#define MUL   5
#define SGN   6
#define DIV   7
#define RECIP   8
#define MOD   9
#define ABS   10
#define MIN   11
#define FLOOR   12
#define MAX   13
#define CEIL   14
#define PWR   15
#define EXP   16
#define LOG   17
#define LOGE   18
#define CIR   19
#define PI   20
#define COMB   21
#define FAC   22

#define DEAL   23
#define RAND   24
#define DRHO   25
#define MRHO   26
#define DIOT   27
#define MIOT   28
#define ROT0   29
#define REV0   30
#define DTRN   31
#define MTRN   32
#define DIBM   33
#define MIBM   34

#define GDU   35
#define GDUK   36
#define GDD   37
#define GDDK   38
#define EXD   39
#define SCAN   40
#define EXDK   41
#define SCANK   42
#define IPROD   43
#define OPROD   44
#define QUAD   45
#define QQUAD   46
#define BRAN0   47
#define BRAN   48
#define DDOM   49
#define MDOM   50

#define COM   51
#define RED   52
#define COMK   53
#define REDK   54
#define ROT   55
#define REV   56
#define ROTK   57
#define REVK   58
#define CAT   59
#define RAV   60
#define CATK   61
#define RAVK   62

#define PRINT   63
#define QUOT   64
#define ELID   65
#define CQUAD   66
#define COMNT   67
#define INDEX   68
#define HPRINT   69

#define LT   71
#define LE   72
#define GT   73
#define GE   74
#define EQ   75
#define NE   76
#define AND   77
#define OR   78
#define NAND   79
#define NOR   80
#define NOT   81
#define EPS   82
#define MEPS   83
#define REP   84
#define TAKE   85
#define DROP   86
#define ASGN   88
#define IMMED   89


#define NAME   90
#define CONST   91
#define FUN   92
#define ARG1   93
#define ARG2   94
#define AUTO   95
#define REST   96

#define COM0   97
#define RED0   98
#define EXD0   99
#define SCAN0   100
#define BASE   101
#define MENC   102   /*   monadic   encode   */
#define LABEL   103   /* statement label */

/*
 * Immediate sub-op codes
 */

#define   CLEAR   1
#define   DIGITS   2
#define   EDIT   3
#define   ERASE   4
#define   FNS   5
#define   FUZZ   6
#define   READ   7
#define   ORIGIN   8
#define   VARS   9
#define   WIDTH   10
#define   DEBUG   11
#define OFF   12
#define LOAD   13
#define SAVE   14
#define COPY   15
#define CONTIN   16
#define LIB   17
#define DROPC   18

struct
{
   char   c[0];
};

data   zero;
data   one;
data   pi;
data   maxexp;
data   datum;
data   getdat();

struct
{
   double   fuzz;
   int   iorg;
   int   digits;
   int   width;
} thread;

/*
 * Types
 */

#define   DA   1
#define   CH   2
#define   LV   3
#define   QD   4
#define   QQ   5
#define   IN   6
#define   EL   7
#define   NF   8
#define   MF   9
#define   DF   10
#define QC   11

struct item
{
   char   rank;
   char   type;
   int   size;
   int   index;
   data   *datap;
   int   dim[0];
} *stack[STKS], **sp;

struct nlist
{
   char   use;
   char   type;   /* == LV */
   int   *itemp;
   char   *namep;
   int   label;
} nlist[NLS];

struct labtab
{
   int   ptr;
   int   siz;
} labtb[MAXLAB];

int   (*exop[])();

double   floor();
double   ceil();
double   log();
double   sin();
double   cos();
double   atan();
double   atan2();
double   sqrt();
double   exp();
double   gamma();
double   ltod();

int   integ;
int   signgam;
int   column;
int   intflg;
int   echoflg;
int   ifile;
int   wfile;
int   funlc;
int   debug;
int   ttystat[3];
int   stime[2];
char   *pcp;
int     rowsz;
int   mencflg;
char    *mencptr;
int oldlb[MAXLAB];
int pt;
int syze;
int pas1;


struct
{
   char   rank;
   char   type;
   int   size;
   int   dimk;
   int   delk;
   int   dim[MRANK];
   int   del[MRANK];
   int   idx[MRANK];
} idx;
