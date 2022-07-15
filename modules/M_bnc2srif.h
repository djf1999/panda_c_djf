#ifndef _M_BNC2SRIF_H_
#define _M_BNC2SRIF_H_
#include "M_dimpar.h"

struct M_bnc2srif
{
    char cstaname[5];
    int jd;
    double  sod;
    double  dtrec;
    int nprn,prn[maxchn];     
    char cprn[maxchn][4];
    double  obs[maxtype][maxchn];
    int lli[2][maxchn];
    int ssi[2][maxchn];
    int flag[maxchn];
};

struct T_bnc_rnx_nav{
    char csat[4];
    int inew;
    int nelem;
    double data[35];
};

struct T_bnc_oc_cor{
    char csat[4];
    double nweek;
    double sow;
    double iod;
    double data[16];    //R/A/O C (VEL) (ACCEL) 
};

#endif