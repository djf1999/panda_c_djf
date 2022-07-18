#ifndef _M_UFC_H_
#define _M_UFC_H_

#include "M_dimpar.h"
#include "M_time.h"
#include "M_run_error.h"

struct T_ufc_oh {
   int  nsite;
   char csite[maxsit][len_staname];
   int  nsat;
   char csat[maxsat][len_satname];
   double xsite[3][maxsit];
   double dintv;
   T_ufc_oh(){
    nsite=0;
    memset(csite,0,maxsit*len_staname);
    memset(csat,0,maxsat*len_satname);
    nsat=0;
    dintv=0;
   }
};

struct T_ufc_oi_one{
   double l1;
   double l2;
   double p1;                         // not used for NRTK/PPP_RA 
   double p2;                         // not used for NRTK/PPP_RA
   double elev,azim;
   int    iflag;
};

struct T_ufc_oi{
   T_time T;
   T_ufc_oi_one DAT[maxsit][maxsat];
};

void read_ufc_oh(int&lun, T_ufc_oh&HD);

void read_ufc_oi(int&lun,T_ufc_oh&HD,T_ufc_oi&REC,int&ierr);


#endif