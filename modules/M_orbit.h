/******* Original Forthan code
!
!! satellite structure parameter for atmosphere drag and solar radiation
!! The defination is now only for panels of  plane-form
!!
module M_orbit
  use M_dimpar 
  use M_time 
  use M_file
  use M_force_model

  integer*4, parameter :: nextend_points=5
!
!! this is also as header of orbit-file
   type T_orbit_header
!
!! satelilte
      character(len=len_satname) csat_group     ! GNS/LEO
      character(len=len_satname) csat_type      ! type of the satellite set
      character(len=len_parname) cframe         ! reference frame CRS, TRS, TCRS (CRS without ERP)
      integer*4 nsat                            ! # of satellites
      character(len=len_satname) csat(maxsat)   ! satellite name
!
!! integerator control
      logical*4 lpartial                        ! integrate variation eqution
      integer*4 norder_adams,nequ,nepo          ! order of adams numerical method
      real*8  int_step,out_step                 ! integrate footstep and output footstep(seconds)
!
!!time and interval control
logical * 4 lextend                         !yes, time is extended time
type(T_time) T(2)                         !start and stop time
!
!!force model
integer * 4 nforce                          !number of foraces considered
type(T_FORCE_MODEL) FMOD(max_force_model) !force models
!
!!solar model
integer * 4 ::nsys_type = 0
!character(len = 20)::sys_type(maxsys)
!character(len = 20)::sys_type(maxsys)
character(len = 20)::sys_type(20)
character(len = 10) solarModel(20)

!!for output
type(T_time) TREF                         !reference time of ICS(begin time of session)
integer * 4::nsat_cus = 0                    !use customer model satellite number
character(len = len_satname) csat_cus(maxsat) !use customer model satellite
!
!!files(temp.)
!g    type(T_file)  FICS                        !file contains initial value of space craft
!g    type(T_file)  FATT                        !file contains attitude information
!g    type(T_file)  FPAN                        !file contains panel information
!g    type(T_file)  FORB                        !file contains orbit information
!g    type(T_file)  FACC                        !file contains accelerator observations(only for LEO)
end type
!
!!this should be SAT ? ? ?
!!temp.used for satellite
type T_spacecraft
character(len = len_satname) ::cname = ' '  !prn name for GNSS
!name for LEOs
character(len = len_satname) ::csvn = ' '  !svn
character(len = len_satname) ::cospar = ' ' !cospar ID
character(len = len_satname) ::ctype = ' '  !block - type
real * 8 ::tbeg, tend
real * 8 ::mass = 0.d0
real * 8 ::area = 0.d0
real * 8 ::yaw_bias = 0.d0
real * 8 ::yaw_max = 0.d0
integer * 4 ::ifid = 0            !frequency id for glonass
logical * 4 lhelp
end type


integer * 4, parameter::max_panel = 15
type T_SINGLE_PANEL
character(len = 12) ::cname                             !panel name
real * 8 ::area                                     !area
real * 8 ::drag                                     !drag coefficients
real * 8 ::norm(3)                                  !unit normal vector in space - craft - fixed system
real * 8 ::normj(3)                                 !unit normal vector in CRS
real * 8 ::spec                                     !reflecting coefficient ?
real * 8 ::dif                                      !diffusing coefficient
end type T_SINGLE_PANEL

type T_SAT_PANEL
character(len = len_satname) ::csat                             !name of satellite
integer * 4      ::npanel                           !number of panels
!type(T_SINGLE_PANEL), allocatable::panel(:)          !panel data
type(T_SINGLE_PANEL) panel(max_panel)               !panel data
end type T_SAT_PANEL

integer, parameter::max_planet = 12

type T_planet
!integer * 4 isc, icb, isun
character(len = len_satname) cname                 !name
real * 8  gm                      !gm
real * 8  radius                  !radius
real * 8  xj(6)                   !pos. and vel.in CRS
real * 8  xe(6)                   !pos. and vel.in TRS
real * 8  dist2cb                 !distance to central body
real * 8  dist2sc                 !distance to satellite
end type

type T_planet_info
integer * 4  nplanet
integer * 4  icb                    !central body
integer * 4  isc                    !satellite
integer * 4  isun                   !isun
integer * 4  imoon                  !imoon
type(T_planet) PL(max_planet)
end type

end module M_orbit
***********************/



/**
 * @M_orbit.h
 * @author Jianan Lou
 * @date 2022.7.16
 * @brief  Module M_orbit
 *
 *
 * @details
 * @see
 */

#ifndef _M_ORBIT_H_
#define _M_ORBIT_H_

//satellite structure parameter for atmosphere drag and solar radiation
//The defination is now only for panels of  plane - form

#include"M_dimpar.h"
#include"M_time.h"
#include"M_file.h"
#include"M_force_model.h"	

const int nextend_points = 5;

//this is also as header of orbit - file

typedef struct
{
	//satelilte
	    char csat_group[len_satname];        //GNS / LEO
		char csat_type[len_satname];         //type of the satellite set
		char cframe[len_parname];            //reference frame CRS, TRS, TCRS(CRS without ERP)
		int nsat;                            //# of satellites
		char csat[maxsat][len_satname];      //satellite name

	//integerator control
		bool lpartial;                       // integrate variation eqution
		int norder_adams, nequ, nepo;        // order of adams numerical method
		double  int_step, out_step;          // integrate footstep and output footstep(seconds)

	//time and interval control
		bool lextend;                        // yes, time is extended time
		T_time T[2];                         // start and stop time
		
	//force model
		int nforce;                          //number of foraces considered
		T_FORCE_MODEL FMOD[max_force_model][T_FORCE_MODEL]; //force models

	//solar model
		int nsys_type = 0;
		// character(len = 20)::sys_type(maxsys)
		// character(len = 20)::sys_type(maxsys)
		char sys_type[20][20]; 
		char solarModel[20][10]; 

	//for output
		T_time TREF;                         //reference time of ICS(begin time of session)
		int nsat_cus = 0;                    //use customer model satellite number
		char csat_cus[maxsat][len_satname];  //use customer model satellite
		
		//files(temp.)
		//g    type(T_file)  FICS                        //file contains initial value of space craft
		//g    type(T_file)  FATT                        //file contains attitude information
		//g    type(T_file)  FPAN                        //file contains panel information
		//g    type(T_file)  FORB                        //file contains orbit information
		//g    type(T_file)  FACC                        //file contains accelerator observations(only for LEO)
}T_orbit_header;

//this should be SAT ? ? ?
//temp.used for satellite
typedef struct
{
	char cname[len_satname] = " ";  //prn name for GNSS
	//name for LEOs
	char csvnp[len_satname] = " ";  //svn
	char cospar[len_satname] = " "; //cospar ID
	char ctype[len_satname] = " ";  //block - type
	double tbeg, tend;
	double mass = 0.0;
	double area = 0.0;
	double yaw_bias = 0.0;
	double yaw_max = 0.0;
	int ifid = 0;            //frequency id for glonass
	bool lhelp;
}T_spacecraft;

const int max_panel = 15;

typedef struct
{
	char cname[12];                             //panel name
	double area;                                //area
	double drag;                                 //drag coefficients
	double norm[3];                             //unit normal vector in space - craft - fixed system
	double normj[3];                            //unit normal vector in CRS
	double spec;                                //reflecting coefficient ?
	double dif;                                 //diffusing coefficient
}T_SINGLE_PANEL;

typedef struct
{
	char csat[len_satname];                      //name of satellite
	int npanel;                                  //number of panels
	//type(T_SINGLE_PANEL), allocatable::panel(:)        //panel data
	T_SINGLE_PANEL panel[max_panel];                 //panel data
}T_SAT_PANEL;

const int max_planet = 12;

typedef struct
{
	//integer * 4 isc, icb, isun
	char cname[len_satname]; // name
	double gm;                      //gm
	double radius;                  //radius
	double xj[6];                   //pos. and vel.in CRS
	double xe[6];                   //pos. and vel.in TRS
	double dist2cb;                 //distance to central body
	double  dist2sc;                //distance to satellite

}T_planet;
		

typedef struct
{
	int nplanet;
	int icb;                    //central body
	int isc;                    //satellite
	int isun;                   //isun
	int imoon;                  //imoon
	T_planet PL[max_planet];
}T_planet_info;

#endif //_M_ORBIT_H_