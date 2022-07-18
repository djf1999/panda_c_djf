/******* Original Forthan code
! 
!! rinex observation information
module M_rinex_all
  use M_dimpar
  use M_time 
  use M_log_header

  character (len=*), parameter :: csysids_all_rnx='GCERJSI'
  integer*4, parameter :: maxsys_rnxobs =max(maxsys,7)
! integer*4, parameter :: maxtype_rnxobs=4*8
! integer*4, parameter :: maxtype_rnxobs=5*8
  integer*4, parameter :: maxtype_rnxobs=6*8

  integer*4, parameter :: kobs_shift=5         ! five phases,then ranges

!
!! RINEX clock
  type T_rnxclk_hd
    real*8 ver
    real*8 dintv
    integer*4 ntype
    character*2 :: ctype(6)=(/'  ','  ','  ','  ','  ','  '/)
  end type


  type T_rnxnav_hd
    sequence
    real*8  ver                          ! version  
    character*20 :: ctype=' '            ! data type (O/N/..) 
    character*20 :: csys='UNDEF'         ! satellite system 
                                         ! GPS      G      
                                         ! GALILEO  E       
                                         ! GLONASS  R    
                                         ! BEIDOU   C    
                                         ! SBAS     S    (not used)
                                         ! MIXED    M    
    character*1  :: csysid=' '           ! sat. sys. id (G/E/R/C/S/M)

    character*20 :: cpgm='UNDEF'         ! program name
    character*20 :: crunby='UNDEF'       ! user 
    character*20 :: cdate='UNDEF'        ! data generated

    character*60 :: cbrdg2n=' '          ! detail about brdg2n run

    logical*4    :: lg2n=.false.         ! is glonass coverted to gps format

    real*8       :: leap_seconds=0.d0    ! leap seconds
!
!! ionospehric corrections

!
!! time correction between systems ?    
  end type T_rnxnav_hd

  type T_rnxnav
    character(len=len_satname) csat ! satellite name
    character(len=1) cfmt           ! format g/n (glonass/gps navigation) 

    type(T_time) T
    real*8 week_                    ! GPS week
    real*8 toe_                     ! toe
    real*8 hlth                     ! health
    real*8 leap_sec                 ! leap sec 

    union 
      map 
        real*8 dclock               ! SV clock bias (sec)  (-TauN)
        real*8 dfreq                ! SV relative frequency bias (+GammaN)
        real*8 sod_mf               ! message frame time (sec of day UTC)
        real*8 xpva(9)              ! position, velocity and accelaration in km, km/sec, km/sec/sec
        real*8 ifrequency           ! frequency number
        real*8 aoi                  ! Age of oper. information (days) (E)
        real*8 toffset              ! system time difference from rnxn
        real*8 resvd(9)
      end map 

      map 
       real*8 a0,a1,a2                                 ! line 1
       real*8 aode, crs,    dn,     M0                 ! line 2
       real*8 cuc,  e,      cus,    roota              ! line 3
!
!!     real*8 toe,  cic,    omega0, cis                ! line 4
       real*8       cic,    Omega0, cis
       real*8 i0,   crc,    omega,  Omegadot           ! line 5   
!
!!     real*8 idot, resvd0, week,   resvd1             ! line 6
!!  resvd1 for glonass=ifrequency
       real*8 idot, resvd0,         resvd1             
!
!!     real*8 accu, hlth,   tgd,    aodc               ! line 7
       real*8 accu,         tgd,    aodc                           
      end map 

      map 
       real*8 zero(24)
      end map

    end union 

  end type T_rnxnav

!
!! obs. type for each system in header
  type T_rnxobs_type
    sequence
!
!! G/R/E/C/S
    character(len=1) :: csysid=' '
    integer*4 :: ntype=0
!
!! type, band, attribute
!! type C/L/D/S/I/X
!! bamd 1/2/5/6/7/8/0
!! attribute P/C/Y/M/N  A/B/C/I/Q/S/L/X/W/Z/" "
!!
    character(len=3) ctype(maxtype_rnxobs)
    real*8 :: shift(maxtype_rnxobs)=0.d0           ! phase shift in rinex header 
  end type
!
!! observation
  type T_rnxobs_hd 
    sequence
    logical*4 lnew                       ! new header
    real*8  ver                          ! version  
    character*20 :: ctype='UDEF'         ! data type (O/N/..) 
    character*20 :: csys='UNDEF'         ! satellite system (G/E/R/C/M)   

    character*20 :: cpgm='UNDEF'         ! program name
    character*20 :: crunby='UNDEF'       ! user 
    character*20 :: cdate='UNDEF'        ! data generated

    character*20 :: cobserver='UNDEF'    ! 
    character*20 :: cagency='UNDEF'

    character*60 :: cmarker_name='UNDEF'  
    character*20 :: cmarker_number='UNDEF' 
    character*20 :: cmarker_type='UNDEF' 

    character*20 :: creceiver_type='UNDEF'
    character*20 :: creceiver_number='UNDEF'
    character*20 :: cantenna_type='UNDEF'
    character*20 :: creceiver_version='UNDEF'
    character*20 :: cantenna_number='UNDEF'
!
!! not tested
    character*10 :: cdcbtype='    '

    character*3 :: cpco_type='UNDEF'     ! ENU or XYZ
    real*8 xpco(3)                       ! PCO from benchmark to ARP  
    real*8 xyz(3)
!
!!  integer*4 fact1,fact2
!
!! new for version 3.xx
    integer*4 :: nsys=0 
    type(T_rnxobs_type) OBST(0:maxsys_rnxobs)

    real*8 dintv
!
!! usually not used
    integer*4 nsat
    character(len=3) csat(maxsat)

    type(T_time) T(2)
   end type T_rnxobs_hd

   type T_rnxobs_1sat
     character*4 cname                   ! for what ?
     character(len=len_satname) csat
     real*8 obs(maxtype_rnxobs)
     integer*4 lli(maxtype_rnxobs)
     integer*4 ssi(maxtype_rnxobs)
     integer*4 iflag                     ! edit flag
     integer*4 :: iflag_last = 0         ! save the flag of last epoch (added by xldai)

   end type

!
!! for modelling
   type T_modobs_1sat_1type
     real*8 :: omc = 0.d0                 ! observed  minus computed   
     character*4 :: camb = '  '           ! ambiguity name AMB1/AMB2/AMBC
     integer*4 :: ipt=0                   ! local index of ambiguity parameters
     integer*4 :: npar=0                  ! number of parameters      
! the parameter may be the same for all or part of the observations
! but the coefficients may differ from obs. to obs., they must be defined
! on the obs.type.
                                          ! ambiguity, inter-channel bias ?
!                                         ! slant delay
     integer*4 :: ipar(maxpar_type)=0     ! ipos of parameters
     logical*4 :: lfix=.false.            ! if this ambiguity fixed or not  !! dxl
     real*8    :: ambini=0.d0             ! ambiguity initial value  !! dxl

   end type

   type T_modobs_1sat        
     real*8 azim
     real*8 elev
!    real*8 azim_ant                      ! elevation in antenna system
!    real*8 elev_ant                      ! for phase windup and PCV

     real*8 mw(4)                         ! nobs, mean, std of the mean in cycles
                                          !    mw(4)  is the current mw obs for test
                                          !    of upd estimation
!
     real*8 t_lastepo
     real*8 delay
!
!! phase-windup
     logical*4 :: lfirst=.true.
     real*8    :: phi_previous = 0.d0

     integer*4 :: npar=0                   ! number of satellite-receiver pair related parameters 
                                           ! system biases
     integer*4 :: ipar(maxpar_pair)=0      ! index of the parameters
     type(T_modobs_1sat_1type) TY(maxtype)
   end type

   type T_obsequ
     integer*4 npar(0:maxtype)
     integer*4 ipt(maxpar_sta+2*maxtype)
     real*8    a(1:maxpar_sta+2*maxtype)
     real*8    wgt(maxtype)
     real*8    omc(maxtype)
     real*8    trop_std                   ! initial slant total delay 
     real*8    trop_dmap                  ! initial slant total delay 
   end type


   type T_log_info
     real*8 :: lifamb(2) = (/0.d0,0.d0/)  ! active ambiguity, start&end time
     logical*1 :: lamb_used = .false.     !
     real*8 :: spndel(2) =(/0.d0,0.d0/)   ! active removed       
     real*8 ::  cycle(2) =(/0.d0,0.d0/)   ! estimated cycles
   end type


   type T_rnxobs
     type(T_time) T
     real*8 dtrcv
     integer*4 nsat
     integer*4 iflag
     type(T_rnxobs_1sat) O(maxsat)

     type(T_log_header) LHD
!
!! allocatable
     logical*4 :: l_allocated=.false.
     type(T_modobs_1sat),allocatable :: M(:)   ! maxsat
     type(T_obsequ), allocatable ::  A(:)

     type(T_log_info),  allocatable ::  L(:)

   end type
!
 contains

   logical*4 function l_alloc_rnxobs(R)

   implicit none
   type(T_rnxobs) R

   integer*4 ioerr

!  write(*,*) ' alloc_rnxobs maxsat=',maxsat
   allocate(R%M(1:maxsat),R%A(1:maxsat),R%L(1:maxsat),stat=ioerr)

   l_alloc_rnxobs=ioerr.eq.0

   R%l_allocated=l_alloc_rnxobs

   return
   end function 


   logical*4 function l_dealloc_rnxobs(R)

   implicit none
   type(T_rnxobs) R

   integer*4 ioerr

   deallocate(R%M,R%A,R%L,stat=ioerr)

   l_dealloc_rnxobs=ioerr.eq.0

   R%l_allocated=.not.l_dealloc_rnxobs

   return
   end function


   subroutine init_rnxobs(R)
  
   implicit none
   type(T_rnxobs) R  

   integer*4 i
   
   R%T=T_time (' ',0,0.d0)
   R%dtrcv=0.d0
   R%nsat=0
   R%iflag=0
   R%O(1:maxsat)%cname=' '
   R%O(1:maxsat)%csat =' '
   do i=1,maxtype_rnxobs
     R%O(1:maxsat)%obs(i)=0.d0
     R%O(1:maxsat)%lli(i)=0
     R%O(1:maxsat)%ssi(i)=0
   enddo

   return
   end subroutine

end module
*****************************/



/**
 * @M_rinex_all.h
 * @author Jianan Lou
 * @date 2022.7.16
 * @brief  Module M_rinex_all
 *
 *
 * @details
 * @see
 */


#ifndef _M_RINEX_ALL_H_
#define _M_RINEX_ALL_H_

//rinex observation information
#include"M_dimpar.h"
#include"M_time.h"
#include"M_log_header.h"
#include"stdafx.h"

const char csysids_all_rnx[15] = "GCERJSI"; 
const int maxsys_rnxobs = max(maxsys, 7);
//integer * 4, parameter::maxtype_rnxobs = 4 * 8
//integer * 4, parameter::maxtype_rnxobs = 5 * 8
const int maxtype_rnxobs = 6 * 8;

const int kobs_shift = 5;         //five phases, then ranges

//RINEX clock
typedef struct
{
	double ver;
	double dintv;
	int ntype;
	char ctype [6][2] = { '  ', '  ', '  ', '  ', '  ', '  ' };
}T_rnxclk_hd;

typedef struct
{
	double  ver;                          //version
	char ctype[20] = " ";             //data type(O / N / ..)
	char csys[20] = "UNDEF";         //satellite system
		//GPS      G
		//GALILEO  E
		//GLONASS  R
		//BEIDOU   C
		//SBAS     S(not used)
		//MIXED    M
	char csysid = ' ';               //sat.sys.id(G / E / R / C / S / M)

	char cpgm[20] = "UNDEF";         //program name
	char crunby[20] = "UNDEF";       //user
	char cdate[20] = "UNDEF";        //data generated

	char cbrdg2n[60] = " ";         //detail about brdg2n run

	bool lg2n = false;         //is glonass coverted to gps format

	double leap_seconds = 0.0;    //leap seconds
		
		//ionospehric corrections

		//
		//time correction between systems ?
}T_rnxnav_hd;


typedef struct
{
	double ver;                          //version
	char ctype[20] = " ";     //data type(O / N / ..)
	char csys[20] = "UNDEF";  //satellite system
		//GPS      G
		//GALILEO  E
		//GLONASS  R
		//BEIDOU   C
		//SBAS     S(not used)
		//MIXED    M
	char csysid = ' ';          //sat.sys.id(G / E / R / C / S / M)

	char cpgm[20] = "UNDEF";         //program name
	char crunby[20] = "UNDEF";       //user
	char cdate[20] = "UNDEF";        //data generated

	char cbrdg2n[60] = " ";          //detail about brdg2n run

	bool lg2n = false;         //is glonass coverted to gps format

	double leap_seconds = 0.0;    //leap seconds
		//
		//ionospehric corrections

		//
		//time correction between systems ?
}T_rnxnav_hd;

typedef struct
{
	char csat[len_satname];     //satellite name
	char cfmt;                  //format g / n(glonass / gps navigation)

	T_time T;
	double week_;                    //GPS week
	double toe_;                     //toe
	double hlth;                     //health
	double leap_sec;                 //leap sec

	union 
	{		
		double dclock;              //SV clock bias(sec)  (-TauN)
		double dfreq;              //SV relative frequency bias(+GammaN)
		double sod_mf;          //message frame time(sec of day UTC)
		double xpva[9];              //position, velocity and accelaration in km, km / sec, km / sec / sec
		double ifrequency;           //frequency number
		double aoi;             //Age of oper.information(days) (E)
		double toffset;              //system time difference from rnxn
		double resvd[9];

		double a0, a1, a2;						//line 1
		double aode, crs, dn, M0;               //line 2
		double cuc, e, cus, roota;              //line 3

		//real * 8 toe, cic, omega0, cis        //line 4
		double cic, Omega0, cis;
		double i0, crc, omega, Omegadot;        //line 5

		//real * 8 idot, resvd0, week, resvd1   //line 6
		//resvd1 for glonass = ifrequency
		double idot, resvd0, resvd1;

		//real * 8 accu, hlth, tgd, aodc        //line 7
		double accu, tgd, aodc;	
		double zero[24];
	};		

}T_rnxnav;

//obs.type for each system in header
typedef struct
{
	//G / R / E / C / S
	char csysid = ' ';
	int ntype = 0;

	//type, band, attribute
	//type C / L / D / S / I / X
	//bamd 1 / 2 / 5 / 6 / 7 / 8 / 0
	//attribute P / C / Y / M / N  A / B / C / I / Q / S / L / X / W / Z / " "
	//
	char ctype[maxtype_rnxobs][3];
	double shift[maxtype_rnxobs] = { 0.0 };           //phase shift in rinex header
}T_rnxobs_type;

	 
//observation
typedef struct
{
	bool lnew;                       //new header
	double ver;                      //version
	char ctype[20] = "UDEF";         //data type(O / N / ..)
	char csys[20] = "UNDEF";         //satellite system(G / E / R / C / M)

	char cpgm[20] = "UNDEF";         //program name
	char crunby[20] = "UNDEF";      //user
	char cdate[20] = "UNDEF";       //data generated

	char cobserver[20] = "UNDEF";   //
	char cagency[20] = "UNDEF";

	char cmarker_name[60] = "UNDEF";
	char cmarker_number[20] = "UNDEF";
	char cmarker_type[20] = "UNDEF";

	char creceiver_type[20] = "UNDEF";
	char creceiver_number[20] = "UNDEF";
	char cantenna_type[20] = "UNDEF";
	char creceiver_version[20] = "UNDEF";
	char cantenna_number[20] = "UNDEF";
	//
	//not tested
	char cdcbtype[10] = "    ";

	char cpco_type[4] = "   ";     //ENU or XYZ
	double xpco[4];                //PCO from benchmark to ARP
	double xyz[3];
	
	//integer * 4 fact1, fact2

	//new for version 3.xx
	int nsys = 0;
	T_rnxobs_type OBST[maxsys_rnxobs + 1];

	double dintv;
	//usually not used
	int nsat;
	char csat[maxsat][3];
	T_time T[2];
}T_rnxobs_hd;
	  
typedef struct
{
	char cname[4];                   //for what ?
	char csat[len_satname];
	double obs[maxtype_rnxobs];
	int lli[maxtype_rnxobs];
	int ssi[maxtype_rnxobs];
	int iflag;                  //edit flag
	int iflag_last = 0;         //save the flag of last epoch(added by xldai)
}T_rnxobs_1sat;

typedef struct
{
	//for modelling
	double omc = 0.0;              //observed  minus computed
	char camb[4] = "  ";           //ambiguity name AMB1 / AMB2 / AMBC
	int ipt = 0;                   //local index of ambiguity parameters
	int npar = 0;                  //number of parameters
	//the parameter may be the same for all or part of the observations
	//but the coefficients may differ from obs.to obs., they must be defined
	//on the obs.type.
	//ambiguity, inter - channel bias ?
	//slant delay
	int ipar[maxpar_type] = { 0 };     //ipos of parameters
	bool lfix = false;                 //if this ambiguity fixed or not !!dxl
	double ambini = 0.0;               //ambiguity initial value  !!dxl
}T_modobs_1sat_1type;

typedef struct
{
	double azim;
	double elev;
	//double azim_ant;                      //elevation in antenna system
	//double elev_ant;                      //for phase windup and PCV

	double mw[4];                           //nobs, mean, std of the mean in cycles
	//mw(4)  is the current mw obs for test
	//of upd estimation
	//
	double t_lastepo;
	double delay;
	//
	//phase - windup
	bool lfirst = true;
	double phi_previous = 0.0;

	int npar = 0;                   //number of satellite - receiver pair related parameters
	//system biases
	int ipar[maxpar_pair] = { 0 };  //index of the parameters
	T_modobs_1sat_1type TY[maxtype];
} T_modobs_1sat;
 
typedef struct
{
	int npar[maxtype + 1];
	int ipt[maxpar_sta + 2 * maxtype];
	double  a[maxpar_sta + 2 * maxtype];
	double  wgt[maxtype];
	double  omc[maxtype];
	double  trop_std;              //initial slant total delay
	double  trop_dmap;             //initial slant total delay
}T_obsequ;
	
typedef struct
{
	double lifamb[2] = { 0.0, 0.0 };  //active ambiguity, start&end time
	bool lamb_used = false;  //
	double spndel[2] = { 0.0, 0.0 };  //active removed
	double cycle[2] = { 0.0, 0.0 };  //estimated cycles
}T_log_info;
	 
typedef struct
{
	T_time T;
	double dtrcv;
	int nsat;
	int iflag;
	T_rnxobs_1sat O[maxsat];
	T_log_header LHD;
	//allocatable
	bool l_allocated = false;
	T_modobs_1sat *M; //maxsat
	T_obsequ *A;
	T_log_info *L;
}T_rnxobs;

#endif //_M_RINEX_ALL_H_