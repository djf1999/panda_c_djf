/******* Original Forthan code
   module m_lsq_control
   use m_dimpar
   use m_time
   use m_file
   use m_ics

   type T_lsq_control
     type (T_time) T(2)                         // begin&end time of the session
     real*8 dintv                               // sampling interval, seconds

     character(len=6) cframe                    // orbit reference frame CRS/TRS/NOERP

     integer*4 nicst                            // number of dynamic orbits

     character(len=10) :: csysbias='SYSTEM+CON' // CHANNEL/SYSTEM/AUTO/NONE
                                                // CHANNEL  -- for all system one parameter each sat-rec pair 
                                                // SYSTEM   -- for all system one parameter each system
                                                // AUTO     -- GLONASS uses CHANNEL others SYSTEM
                                                // NONE     -- not estimated
                                                // CON/RWK  -- constant or random-walk process
     character(len=20) :: csysmode=''

     integer*4 :: nsat =0                       // number of satellites
     character(len=len_satname) csat(maxsat)                   // satellite prn
     integer*4 :: nsite=0                       // number of stations
     character(len=len_staname) csite(maxsit)                  // station name

     integer*4 :: npcv=0                        // number of PCVs
     character*20 spcv                          // pcv correcton model
     character*80 tide_correction               // tidal deformation corrections
     integer*4 nobstype
     integer*4 nambtype                         // for allocation of NEQ

     character*4 obstype(maxtype)               // obs. type
     character*4 obsmode(maxtype)               // differential mode 
     character*4 obsweight                      // weighting strategy for observations
     logical*4 l_epodif,l_mixed

     character*20 cestimator                    // EPO/BAT
     character(len=1) cambfix                   // S/R/N  for Search/Round/No
     logical*4 l_use_ambcon                     // apply ambcon
     logical*4 l_remove_bias                    // remove inactive ambiguities
     logical*4 l_remove_ztd                     // remove inactive ambiguities
     logical*4 l_output_omc                     // output omc for NRTK
     logical*4 l_output_neq                     // output neq-file
     logical*4 :: l_output_var=.false.                     // output neq-file
     logical*4 lsnxFile
!
     logical*4 :: l_constraint_amb=.false.      // constraint ambiguities  
     real*8    :: amb_sigma=0.d0

!! ionospehric delays                           // estimate ionospheric slant delays
     logical*4  :: l_iono=.false.
£¡
!! SRIF quality control
     logical*4  :: l_pre_qc=.false.

!! SRIF quality control
     logical*4 l_qc
     real*8 max_postfit_rms
     real*8 max_resmax
!
!! channel filter
     logical*4 l_chn_filter
     real*8 lglimit,lwlimit,gaplimit
!
!! stream observations
     character*40 shmid_satclk_in
     character*40 shmid_satclk_out
     logical*4 l_stream
     character*40  host                         // for NtripTool
     character*40  port                         // for NtripTool
     character*40  shmid                        // for both NtripTool and SRIF

     real*8 intv_orbit_update                      // in seconds 

     T_file FRES                          // residual file
     T_file FOMC                          // residual file
     T_file FPAR_RM                       // recovered parameters
     T_file FPAR_VAR                      // parameters with covariation
     T_file FNEQ                          // NEQ file
     T_file FAMBCON                       // file with integer-ambiguity contraints
     T_file FAMBCOR
     T_file FAMBINP                       // output for ambiguity-fixing  
     T_file FPAR                          // parameter file
     T_file FPAR_korb                     // parameter file for real-time orbit
     T_file FSCLK, FRCLK                  // satellite and receiver clocks
     T_file FKSCLK                        // output real-time satellite clocks 
     T_file FKSATPOS                      // output real-time satellite clocks 
     T_file FORB                          // GNSS orbits
     T_file FICS
     T_file FZTD  
     T_file FZGE  
     T_file FZGN  
     T_file FMSJ                          // mini-second jumps
     T_file FAMB                          // epoch-ambiguity for UPD estimation
     T_file FYAW                          // yaw files  
     T_file FSNX                          // sinex file
  end type
end  module m_lsq_control
****************************/

/**
 * @M_lsq_control.h
 * @author Jianan Lou
 * @date 2022.7.16
 * @brief  Module M_lsq_control
 *
 *
 * @details
 * @see
 */

#ifndef _M_LSQ_CONTROL_H_
#define _M_LSQ_CONTROL_H_

#include"M_dimpar.h"
#include"M_time.h" 
#include"M_file.h" 
#include"M_ics.h" 

typedef struct 
{
	T_time T[2];
	double dintv;                                //sampling interval, seconds
	char cframe[6];                              // orbit reference frame CRS / TRS / NOERP
	int nicst;                                   // number of dynamic orbits
	char csysbias[11] = "SYSTEM+CON";            // CHANNEL/SYSTEM/AUTO/NONE
		                                         // CHANNEL  -- for all system one parameter each sat-rec pair 
		                                         // SYSTEM   -- for all system one parameter each system
		                                         // AUTO     -- GLONASS uses CHANNEL others SYSTEM
		                                         // NONE     -- not estimated
		                                         // CON/RWK  -- constant or random-walk process
	char csysmode[20] = "";
	int  nsat = 0;                               // number of satellites
	char csat[maxsat][len_satname];              // satellite prn
	int  nsite = 0;                              // number of stations
	char csite[maxsit][len_staname];             // station name
	int npcv = 0;                                // number of PCVs
	char spcv[20];                               // pcv correcton model
	char tide_correction[80];                    // tidal deformation corrections
	int nobstype;
	int nambtype;                                // for allocation of NEQ

	char obstyoe[maxtype][4];                    // obs. type
	char obsmode[maxtype];                       // differential mode 
	char obsweight[4];                           // weighting strategy for observations
	bool l_epodif, l_mixed;
	char cestimator[20];                         // EPO/BAT
	char cambfix;                                // S/R/N  for Search/Round/No
	bool l_use_ambcon;                           // apply ambcon
	bool l_remove_bias;                          // remove inactive ambiguities
	bool l_remove_ztd;                           // remove inactive ambiguities
	bool l_output_omc;                           // output omc for NRTK
	bool l_output_neq;                           // output neq-file
	bool l_output_var = false;                   // output neq-file
	bool lsnxFile;
	
	bool l_constraint_amb = false;               // constraint ambiguities  
	double amb_sigma = 0.0;

   // ionospehric delays                         // estimate ionospheric slant delays
	bool l_iono = false;

   // SRIF quality control
	bool l_pre_qc = false;

   // SRIF quality control
	bool l_qc;
	double max_postfit_rms;
	double max_resmax;

   // channel filter 
	bool l_chn_filter;
	double lglimit, lwlimit, gaplimit;

   // stream observations
	char shmid_satclk_in[40];
	char shmid_satclk_out[40];
	bool l_stream;
	char  host[40];                                       // for NtripTool
	char  port[40];										  // for NtripTool
	char  shmid[40];                                      // for both NtripTool and SRIF
	double intv_orbit_update;                             // in seconds 
	
	T_file FRES;                                          // residual file
	T_file FOMC;                          // residual file
	T_file FPAR_RM;                       // recovered parameters
	T_file FPAR_VAR;                      // parameters with covariation
	T_file FNEQ;                          // NEQ file
	T_file FAMBCON;                       // file with integer-ambiguity contraints
	T_file FAMBCOR;
	T_file FAMBINP;                       // output for ambiguity-fixing  
	T_file FPAR;                          // parameter file
	T_file FPAR_korb;                     // parameter file for real-time orbit
	T_file FSCLK, FRCLK;                  // satellite and receiver clocks
	T_file FKSCLK;                        // output real-time satellite clocks 
	T_file FKSATPOS;                      // output real-time satellite clocks 
	T_file FORB;                          // GNSS orbits
	T_file FICS;
	T_file FZTD;
	T_file FZGE;
	T_file FZGN;
	T_file FMSJ;                          // mini-second jumps
	T_file FAMB;                          // epoch-ambiguity for UPD estimation
	T_file FYAW;                          // yaw files  
	T_file FSNX;                          // sinex file
}T_lsq_control;


#endif //_M_LSQ_CONTROL_H_
