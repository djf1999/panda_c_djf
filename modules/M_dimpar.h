#ifndef _M_DIMPAR_H_
#define _M_DIMPAR_H_

#include <stdio.h>
#include <string.h>

#define    maxsys           7                    //GPS/GLONASS/BEIDOU/GALILEO
#define    csysids_all      "GCERIJ"     
#define    maxisx           5
#define    maxifb           30
                                                 // this is only used for rinex-file
// #define    maxsat        90                   // max. number of sateliltes
// #define    maxsit        450                  // max. number of sites
#define    maxsat           125                  // max. number of sateliltes
#define    maxsit           150                  // max. number of sites
// #define    maxsit        300                  //max. number of sites

#define    maxeph_sat       24*2*3               // max. number of records of broadcast ephemeris
                                                 // per satelite, each every half hour for three days
// #define    maxeph        maxsat*maxeph_sat    // max. number of records of broadcast ephemeris
// maxeph     maxeph        10000                // max. number of records of broadcast ephemeris
#define    maxeph           10000                // max. number of records of broadcast ephemeris
// #define    maxeph           20000             // max. number of records of broadcast ephemeris

#define    maxfreq          3                    // max. number of observation types in rinex file 
#define    maxtype          maxfreq *5           //CN?,PN?,LN?

// #define    maxtype_in_rnxhd 30                //max. type in rinex file
// #define    maxpar_sta       300               //temp
#define    maxpar_sta       300                  //temp
// #define    maxpar_sat       300               //temp
#define    maxpar_sat       30                   //temp
#define    maxpar_pair      4                    //max. number for a station-satellite pair
                                                 //  iono. slant delay, inter-system
#define    maxpar_type      4                    //integer-frequency/channel bias,  ambiguities
#define    maxchn           12*3                 //max. number of channels of GPS receiver 

#define    maxicst          maxsat               // max. number of type of satellite force-model
#define    maxics           50                   //max. number of GNSS parameters   

#define    maxvar           300                  //max. number of LEO parameters   

#define    maxpar           3000                
#define    maxepo           2880                 //max. number of epochs (30sec) for ambiguity fixing  
#define    maxepo_1s        maxepo*300           //max. number of epochs 1sec) 
#define    maxant           50                   //max. number of antenna PCVs

#define    len_filename     256                  //max. length of string for file-name 
#define    len_longstr      256                  //max. length of string for information

#define    len_satname      20                   //max. length of satellite name        
#define    len_staname      20                   //max. length of station name 
#define    len_parname      30                   //max. length of parameter name

#define    maxpwc_force     48
#define    maxLeo           4
#define    maxequ_leo       2*maxvar

#define    maxdif_files     400

#endif