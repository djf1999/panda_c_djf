#ifndef _M_UPD_H_
#define _M_UPD_H_
//#include"M_time.h"
#include "M_constant.h"
 
  const double freqpcGPS=102300000.0;
  const double f1GPS=154.0;
  const double f2GPS=120.0;

  const double wlength_l1 = vlight/freqpcGPS/f1GPS;
  const double wlength_l2 = vlight/freqpcGPS/f2GPS;
  const double wlength_lw = vlight/freqpcGPS/(f1GPS-f2GPS);
  const double wlength_ln = vlight/freqpcGPS/(f1GPS+f2GPS);


struct T_epoch_amb{
    int    iprn;
    int    jd;
    double sod, sod1;
    double bc, sbc;
    double bw, sbw, bw0;
    double bn;  
    int    ifixed;
    bool   l_newarc;
    int    nepo;
    double elev;
    double bwi; 
    T_epoch_amb (){
      ifixed=0;
      l_newarc=true;
      nepo=0;
    }
};

struct T_upd{
    char cobj[10];
    int npoint=0;  
    double tepo=0.0;
    double x=0.0;
    double s=1e4; 
    double lref=false;
};

void init_upd(T_upd& UPD);

#endif