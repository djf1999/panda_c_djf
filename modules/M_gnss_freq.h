#ifndef _M_GRNSS_FREQ_H_
#define _M_GRNSS_FREQ_H_
#include "M_dimpar.h"

struct T_trans_freq{
    char  csysid[3];               // sysid or satellite name (glonass)
    char  cfreq_band[5];           //    
    char  cfreq_id;                // observation level
    double freq;                           // frequency in Hz
    double wlength;                        // wavelength in m
    T_trans_freq(){
        memset(csysid,0,3);
        memset(cfreq_band,0,5);
    }
    T_trans_freq(char a1,char* a2,char a3,double a4,double a5){
        memset(csysid,0,3);
        memset(cfreq_band,0,5);
        csysid[0]=a1;
        strcpy(cfreq_band,a2);
        cfreq_id=a3;
        freq=a4;
        wlength=a5;
    }
};

struct T_freq_basic{
    int nfreq;
    T_trans_freq  FREQ[7];
};

static int  nsys_in_freq = 0;  
static T_freq_basic SYSFREQ[7]; 

void set_sat_freq_basic();

#endif