#ifndef _M_DCB_H_
#define _M_DCB_H_
#include "M_dimpar.h"
//
// DCB correction
struct T_dcb{
    char csat[len_satname];
//
// system (G/R/E/C/J/...)
// band   1/2/...
// attributes P/C ...
//
//
// P1P2  P1C1 P2C2, in meter
    double rawcor[3];
// P1/P2/C1/C2/X2, in meter
    double cor[5];
    T_dcb()
    {
        memset(csat,0,len_satname);
        memset(rawcor,0,3);
        memset(cor,0,5);
    };

};

  static bool l_read_dcb=false;
  static int  nsat_dcb=0;
  static T_dcb DCB[maxsat];
#endif