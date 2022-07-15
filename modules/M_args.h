#ifndef _M_ARG_H_
#define _M_ARG_H_

#include "M_dimpar.h"

struct T_ARG{
   char   name[12];
   int    nmin;
   int    nmax;
   int    npar;
   char   pars[40][128];
   T_ARG():nmin(0),nmax(0),npar(0){
      memset(name,0,12);
      memset(pars,0,40*128);
   };
};
int narg;

int MAXARG;
T_ARG* ARG;

void l_alloc_args(int maxarg);

void l_dealloc_args();

void get_switches();

#endif