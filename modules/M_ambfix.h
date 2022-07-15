#ifndef _M_AMBFIX_H_
#define _M_AMBFIX_H_
#include"M_dimpar.h"
#include"M_time.h"
#include"M_file.h"

const int    maxamb_bl=2000;         //max. number of dd-ambiguities over a baseline
sonst int    maxamb_per_pair=600 ;   //PPP amb. fixing

struct T_baseline{
     int ista1;
     int ista2;
     double  length ;                 //in km
     char  csysids[20] ;            //csysids
};
//
// zero-difference ambiguity
struct T_oneway_ambiguity{
     char cambtype;                //C/1/2/W
     bool selected;     //selected  
     int    ista;                //station index
     int    isat;                //satellite index
     int    ipt;                 //   
     int    iepo1;               //start epoch
     int    iepo2;               //end epoch
     double       t1;
     double       t2;    
     double       rwl;              //real value widelane (cyc)
     double       srwl;             //its sigma
     double       rlc;              //real value lc from slution (m)
     double       srlc;             //its sigma
     T_oneway_ambiguity (){
       ista=0;
       isat=0;
       ipt=0;                  
       iepo1=0;
       iepo2=0;
       
       t1=0.0;
       t2=0.0;     
       rwl=0.0;           
       srwl=0.0;           
       rlc=0.0;         
       srlc=0.0; 
       selected=false ;
       cambtype=' ';
     }
};
//
// double-differece ambiguity
struct T_dd_ambiguity{
     char  cambtype;           //C/1/2/W
     bool    selected;         //selected
     bool    lw_fixed;         //widelane fixed
     bool    ln_fixed;         //narrowlane fixed
     int    ipt2ow[4];         //global index to the four OW ambiguities
     int    ipt2ow_loc[4];     //local index to the foud OW ambiguities
                               //of the baseline for indep. check
     int    iepo1;              //start epoch
     int    iepo2;              //end epoch
     double       rwl,srwl;     //real widelane and its sigma
     double       rnl,srnl;     //real narrowlane and its sigma
     double       rlc,srlc;     //lc ambiguity and its sigma
     int    iwl, inl;           //integer wide- and narrow-lane
     double       factor;                /// 
//
// for ppp
     int    nsd;                  //number SDs contributing to the UPD correction
     double       sd_rnl_cor;     //correction 
     double       sigcor;         //sigma

     T_dd_ambiguity()
     {
        cambtype=' ';
        selected=false;
        lw_fixed=false;
        ln_fixed=false;
        memset(ipt2ow,0,4);
        memset(ipt2ow_loc,0,4);
        iepo1=0;
        iepo2=0;
        rwl=0.0;
        srwl=0.0;
        rnl=0.0;
        srnl=0.0;
        rlc=0.0;
        srlc=0.0;
        iwl=0;
        inl=0;
        nsd=0
        sd_rnl_cor=0.0;
        sigcor=0.0;
     }
};

#endif