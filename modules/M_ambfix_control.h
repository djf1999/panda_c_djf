#ifndef _M_AMBFIX_CONtrol_H_
#define _M_AMBFIX_CONtrol_H_
#include"M_dimpar.h"
#include"M_time.h"
#include"M_file.h"

struct T_ambfix_control
{
     int nambtype ;                    //  number of ambiguity type (L1/L2/LC/LW..)
     char ambtype[maxtype][4];      
     int namb_per_type[maxtype+1];       // start and stop of each type
     bool lfix_sd;                  
     bool ow_solution;             
     char cambfix;                     // R/S/N for Round/Search/No
     bool laddleo;                 // LEO indcluded
     bool lindepend_baseline;      // define independent baseline first
                                       // otherwise, all baseline and the search 

     double max_baseline_length;
     double min_common_time;
     double wl_dintv;
//
//// ambiguity not considered for fixing if its deviation to the nearesst
//// integer is larger than xx_maxdev, or its STD is larger than xx_maxsig.
     double wl_maxdev;                  // limit of deviation
     double wl_maxsig;                  // limit of STD
     double wl_alpha;                   //
     double ratio ;                     // min. ratio to be aceepted for fixing

     double nl_maxdev ;                 // 
     double nl_maxsig;
     double nl_alpha;

//// files
     char flog0[len_filename];               // log-file
     char fobs0[len_filename];               // rinex-file
     char fpar0[len_filename];              // free solution (?)
	 T_file FPAR_FIX;
     T_file FAMBINP;              // NEQ-file
     T_file FAMBCON ;             // fixing constrints
     T_file FUPD_WL ;             // UPD (wide-lane) file 
     T_file FUPD_NL ;             // UPD (narrow-lane)file
//
//// satellites excluded in ambiguity-fixing
     int  nsat_excluded=0;
     char csat_excluded[maxsat][len_satname];
//
//// from LSQ_CTRL
     T_time T[2];                   // begin&end time of the session
     double dintv;                      // sampling interval, seconds
     int namb=0;
     int nsat =0;              // number of satellites
     char csat[maxsat][len_satname] ;         // satellite name (G12)
     double wlength[maxsat][6];          //
     int nsite=0;              // number of stations
     char csite[maxsit][len_staname];         // station name
     char skd[maxsit][4];           // skd

     char obstype[40];              // obs. type
     char remove_bias[20];          // remove inactive ambiguities
};


#endif
