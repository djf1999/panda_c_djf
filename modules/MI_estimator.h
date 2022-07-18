#ifndef _MI_EASTIMATOR_H_
#define _MI_EASTIMATOR_H_
#include "M_dimpar.h"
#include "M_estimator.h"
#include  "M_rinex_all.h"

void add_newamb(bool&l_rm,bool&l_rt,T_time&TEPO,int& isite,int& nsat,int& nobstype,T_parameter&PAR,T_rnxobs&OB,
char*csite,char*csat,T_time&TEND,T_lsq_estimator&LE,T_SquareRootInfo_Filter&SRF);
#endif