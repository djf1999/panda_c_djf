#ifndef _M_CHANNEL_FILTER_H_
#define _M_CHANNEL_FILTER_H_
#include"M_dimpar.h"

struct T_channel_filter{
   int nwm[maxsat];
   double xwm[maxsat];
   double swm[maxsat];
   
   double lgcoef[maxsat][3];  // third order polynomial
   double lgtime[maxsat][3];
   double lg[maxsat][3];
   int nlg[maxsat];
   
   double lg[maxsat];
   double nw[maxsat];
   double lc[maxsat];
   double pc[maxsat];

   bool lfirst[maxsat];
    T_channel_filter()
    {
        memset(nwm,0,maxant*sizeof(int));
        memset(xwm,0,maxant*sizeof(double));
        memset(swm,0,maxant*sizeof(double));
        for(int i=0;i<maxant;i++)
        {
            lgtime[maxsat][0]=0.0;lgtime[maxsat][2]=0.0;lgtime[maxsat][3]=0.0;
            lgcoef[maxsat][0]=0.0;lgtime[maxsat][2]=0.0;lgtime[maxsat][3]=0.0;
            lg[maxsat][0]=0.0;lgtime[maxsat][2]=0.0;lgtime[maxsat][3]=0.0;
        }
        memset(lg,0,maxant*sizeof(double));
        memset(nw,0,maxant*sizeof(double));
        memset(lc,0,maxant*sizeof(double));
        memset(pc,0,maxant*sizeof(double));

        bool lfirst=true;
    }
};

// local 
static T_channel_filter CF[maxsit];

#endif