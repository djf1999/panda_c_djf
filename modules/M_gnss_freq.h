#ifndef _M_GRNSS_FREQ_H_
#define _M_GRNSS_FREQ_H_

struct T_trans_freq{
    char  csysid[3];               // sysid or satellite name (glonass)
    char  cfreq_band[5];           //    
    char  cfreq_id;                // observation level
    double freq;                           // frequency in Hz
    double wlength;                        // wavelength in m
};

struct T_freq_basic{
    int nfreq;
    T_trans_freq  FREQ[7];
};

static int  nsys_in_freq = 0;  
static T_freq_basic SYSFREQ[7]; 

void set_sat_freq_basic();

#endif