#ifndef _M_YAW_H_
#define _M_YAW_H_

#include"M_dimpar.h"

const int  maxeclips=30;

struct T_yaw{     
    char   csat[len_satname];
    char   ctype[len_satname];
    double period;                               //in minutes
    int    neclips;
    double tbeg[maxeclips];                     //seconds of week
    double tend[maxeclips];                     //seconds of week
    int    itype[maxeclips];                  //1 noon, 2 night
    T_yaw(){
        neclips=0;
        memset(csat,0,len_satname);
        memset(ctype,0,len_satname);
    }
};

static bool linited=false;
static int  nweek_yaw;                           //week 
static int  nsat_yaw=0;
static T_yaw TYAWS[maxsat];

#endif