#ifndef _M_GLONASS_FID_H_
#define _M_GLONASS_FID_H_

#include"M_dimpar.h"

// DCB correction
struct T_glonass_frequency{
    char csat[len_satname];
    bool lbrd;
    bool linp; 
    int  ifid_brd;    
    int  ifid_inp;
    T_glonass_frequency(){
        lbrd=false;
        linp=false;
        ifid_brd=0;
        ifid_inp=0;
        memset(csat,0,len_satname);
    }
};

  static int nsat_fid=0;
  static T_glonass_frequency TFID[maxsat];

#endif