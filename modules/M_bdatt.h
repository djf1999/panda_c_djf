#ifndef _M_BDATT_H_
#define _M_BDATT_H_
#include"M_time.h"
#include"M_file.h"

const double YRATE_IGSO = 0.06;
const double ANOON_MEO = 4.0;
const double MAX_YAW = 5.0;
const int  MAX_ECLIPS = 30; 
const int  MAX_BD_SAT = 30;
//
// collective of the ctrl parameters for bdatt
struct T_bdatt_control {
    T_file        FORB;                             // orb file     
    int           nsat;
    char          csat[MAX_BD_SAT][len_satname];
    double        dintv ;               // sampling rate 
    double        orb_intv;            // orb file interval
    T_time        T[2];
    int           dayslength;                        // days
    bool          l_out_angle;          // output beta and u angles
    double        out_intv;             // output interval
    T_file         FANGLE;                 
    T_file         FATT;
    T_bdatt_control ()
    {
        dintv=30.0;
        orb_intv=300.0;
        l_out_angle=false;
        out_intv=30.0;
    }
};
 
struct T_bd_yaw  {  
     char csat[len_satname];
     char ctype[len_satname];
     double period;                                // in minutes
     int neclips;
     T_time  tbeg[MAX_ECLIPS];                      // in jds
     T_time  tend[MAX_ECLIPS];                      // in jds 
     double beta[MAX_ECLIPS];
     double yaw[MAX_ECLIPS];
     int itype[MAX_ECLIPS];                   // 1:normal , 2:fixed
     T_bd_yaw (){
        memset(csat,0,len_satname);
        memset(ctype,0,len_satname);
        neclips=0;
     }
}; 
  
  static T_bd_yaw TBDYAWS[MAX_BD_SAT];
  static bool  isFirst[MAX_BD_SAT];
   
#endif
