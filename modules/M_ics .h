#ifndef _M_ICS_H_
#define _M_ICS_H_

#include"M_dimpar.h"
#include"M_time.h"

// satellite structure parameter for atmosphere drag and solar radiation
// The defination is now only for panels of  plane-form
//
// orbit parameters before time-splitting
struct T_ics_var {
    char   cname[len_parname];     // name
    int    itype;       // 0/1/2 single/pwc/vel.breaks
    int    ipar_start;  // position before the first one 
    int    mpar;        // number of splitting
    int    nactive;      // for obs. equ. of PWC
    double sig0;        // a priori sigma
    double dintv;       // length of the interval. necessary ??? 
    T_ics_var (){
        itype=0;
        memset(cname,0,len_parname);
        ipar_start=0;
        mpar=0;
        nactive=0;
        sig0=0.0;
        dintv=0.0;
    };
};
//
//// orbit parameters after time-splitting
struct T_ics_par {
    int ipar;                      // ipar-th of this splitted varirable
    double xini;                   // initial values
    double xest;                   // estimated
    double sig;                    // sigma
    T_time  T[2];                  // active time interval
    T_ics_par(){
      ipar=0;
      xini=0.0;
      xest=0.0;
      sig=0.0;
    }
};

struct T_ics_info{
    char   csys[len_satname];             // GNS LEO
    char   csubsys[len_satname];          // GPS GRACE
    char   csat[len_satname];             // G01 GRACE-1
    T_time TREF;                          // reference time
    int    nvar;                          // number of variables
    int    npar;                          // number of splitted parameters
    int    nvarall;                       // number of variables including VelBreaks
    int    nparall ;                      // number of splitted parameters including VelBreaks
    T_ics_info(){
      memset(csys,0,len_satname);
      memset(csubsys,0,len_satname);
      memset(csat,0,len_satname);
      nvar=0;
      npar=0;
      nvarall=0;
      nparall=0;
    }
};

struct T_SAT_ICS{
    bool        lcus;
    double      sig0_cus;                     // a priori sigma of Customer model
    T_ics_info  INFO;               // information
    T_ics_var   VAR[maxics];        // varialbe information
    T_ics_par   PAR[maxvar];        // parameter inforamtion
    char        solarMod[20];       // ECOM1 / ECOM2
    T_SAT_ICS(){
      lcus=false;
      sig0_cus=0.0;
      memset(solarMod,0,20);
    }
};

#endif