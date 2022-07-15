#ifndef _M_ISBIFB_H_
#define _M_ISBIFB_H_

#include"M_dimpar.h"
#include "M_time.h"
#include "M_file.h"
#include "M_glonass_fid.h"

//// ISB/IFB defined for SITE
struct T_isb_rec{
    char   csysid;
    double isbVal;
    T_isb_rec(){
        csysid=' ';
        isbVal=0.0; 
    }
};
  
struct T_ifb_rec{
    char csat[len_satname];
    double ifbVal;
    T_ifb_rec(){
        memset(csat,0,len_satname);
        ifbVal=0.0;
    };
};
  
//// inter-system bias
struct T_isb{
    char   parName[maxsys][20];
    double parVal[maxsys];
    double parTime[maxsys][2];
    
    int    ista;
    int    nisb;
    
    char   siteName[len_staname];
    char   rectype[20];
    char   recsnr[20];
    char   recfmw[20];        // receiver firmware
    char   anttype[20];
    char   antsnr[20];

    char   csysids[10];       // system ids from ctrl-file (G,R,C,E and their combination)
    double blh[3];
    T_isb(){
        for(int i=0;i<maxsys;i++){
            parVal[i]=0;
            parTime[i][0]=0;
            parTime[i][0]=0;
        };
        ista=0;
        nisb=0;
        memset(parName,0,20*maxsys);
        memset(rectype,0,20);
        memset(recsnr,0,20);
        memset(recfmw,0,20);
        memset(anttype,0,20);
        memset(antsnr,0,20);
        memset(csysids,0,20);
        blh[0]=0.0;blh[1]=0.0;blh[2]=0.0;
    }
};
  
struct T_ifb{
    char   parName[maxsat][20];
    double parVal[maxsat];
    double parTime[maxsat][2];
    char   satName[maxsat][len_satname];
    int    nifb;
    int    ista;
    int    isat;
    int    ifreq[maxsat];
    char   siteName[len_staname];
    char   rectype[20];
    char   recsnr[20];
    char   recfmw[20];                // receiver firmware
    char   anttype[20];
    char   antsnr[20];

    char   csysids[10];                // system ids from ctrl-file (G,R,C,E and their combination
    T_ifb(){
        for(int i=0;i<maxsys;i++){
            parVal[i]=0;
            parTime[i][0]=0;
            parTime[i][0]=0;
        };
        memset(parName,0,20*maxsat);
        memset(parName,0,20*maxsat);
        memset(ifreq,0,maxsat*sizeof(int));
        memset(siteName,0,len_staname);
        memset(rectype,0,20);
        memset(recsnr,0,20);
        memset(recfmw,0,20);
        memset(anttype,0,20);
        memset(antsnr,0,20);
        nifb=0;
        ista=0;
        isat=0;

    }
};

// type(T_isb), save ::ISB(maxsit)
// type(T_ifb), save ::IFB(maxsit)
// integer*4, save  :: nsite=0

#endif