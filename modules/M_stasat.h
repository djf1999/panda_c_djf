/******* Original Forthan code
   module M_stasat
   use M_dimpar
   use M_time 
   use M_file
   use M_ics
   use M_gnss_freq
   use M_isbifb

!
!! object trajectory/orbit
  type T_object_state
    type (T_time)  :: T         ! epoch time
    real*8         :: x(9)      ! position&velocity (m, m/s, m/s**2 )
    real*8         :: sx(9)     ! sigma
    real*8            pd(3)     ! power density
    real*8         :: geo(3)    ! geographical lat, lon. and height (rad,rad, m)
  end type T_object_state


   type T_clock
     character (len=5) ::  type=' '   ! H/Cs/Ru
     character (len=3) ::  mode=' '   ! REF, CLK
     real*8  :: dclk0 =0.d0           ! Sigma0 of the initial clock offsets 
     real*8  :: qclk  =0.d0           ! POD of clock bias   s/square_root(s)

     integer*4 :: ndgr=0              ! degree of polynomial clock model
                                      ! 0 epochwise, 1 linear, 2 quard.
     type(T_time) TC
     real*8  :: a(3)=(/0.d0,0.d0,0.d0/) !
     real*8  :: dt  =0.d0               ! correction at the epoch 
     integer*4 :: ierr   = 1          ! =0 available, 

     real*8    :: dt_cor = 0.d0
     real*8    :: dt_v = 0.d0
     integer*4 :: icor = 1            ! =0 available
   end type

   type T_trop
      character*10 :: ztdmod=' ' 
      character*10 :: grdmod=' '
      character*4  :: cztd=' '
      character*4  :: cmap=' '
!
!! SEA == sea-level, NOM == using nominal values, STA == at the station
      character*4  :: sealoc=' ' 
      real*8 :: p0=0.d0,t0=0.d0,hr0=0.d0
!
!! zenith delay (total,dry,wet)
      real*8 :: ztd
      real*8 :: zdd
      real*8 :: zwd
      real*8 :: dmap
      real*8 :: wmap
      real*8 :: grde_coeff
      real*8 :: grdn_coeff
      real*8 :: grde
      real*8 :: grdn
!
!! estimated correction
      real*8 :: ztdcor=0.d0
!
!! statistical informaton about the process
      real*8 :: dztd0=0.d0,qztd=0.d0
      real*8 :: dgrd0=0.d0,qgrd=0.d0
   end type


    integer*4, parameter :: MAXFREQ_ANT = 30  !igs14.atx maxfreq=25

    type T_ANT_PCV
      character(len=20) :: anttype=' '
      character(len=20) :: antnum=' '
      character(len=10) :: csvn=' '
      character(len=10) :: cospar=' '
      character(len=1 ) :: rora=' '
      real*8 :: tbeg      ! beginning mjd
      real*8 :: tend      ! end mjd 
      integer*4 ::  nfreq=0
      real*8 :: zen1=0.d0
      real*8 :: zen2=0.d0
      real*8 :: dzen=0.d0
      real*8 :: dazi=0.d0
      character(len=4) cfreq(MAXFREQ_ANT)
      real*8 :: enu(3,MAXFREQ_ANT)=0.d0
      real*8 :: pcv(41,0:300,MAXFREQ_ANT)=0.d0
    end type

 
   type T_station
     type(T_FILE) FOBS        ! obs-file 
     type(T_FILE) FORB        ! orbit-file (LEO dyn), position-file (kin)
     type(T_FILE) FATT        ! attitude-file
     type(T_FILE) FLOG        ! log-file
     type(T_FILE) FICS        ! ics-file
     character (len=len_staname)  :: name= '  '
     character (len=len_staname)  :: name_long= '  '
     character*4  :: csource= 'UNKN'
     character*4  :: cplate = 'UNKN' 
     character*2  :: skd=' '
     real*8 :: cutoff=0.d0
!
!! offset, from benchmark to ref.point
     character*20 :: rectype=' '
     character*10 :: dcbtype=' '
     character*20 :: recsnr =' '
     character*20 :: recfmw =' '      ! receiver firmware
     character*20 :: anttype=' '
     character*20 :: antsnr=' '

     character*10 :: csysids='  '           ! system ids from ctrl-file (G,R,C,E and their combination)
     character*10 :: csysids_receiver = ' ' ! system ids from receiver-file

     real*8 :: enu(3)=0.d0
!
!! obs precision, pseudorange,phase,laser,kbr
     real*8 :: sigr(maxfreq)=0.d0
     real*8 :: sigp(maxfreq)=0.d0
     real*8 :: sigl=0.d0
!
!! position&velocity
     real*8 :: x(9)=0.d0
     real*8 :: geod(3)=0.d0
!    real*8 :: dx0(12)=0.d0
     real*8 :: dx0(12)=(/0.d0,0.d0,0.d0,0.d0,0.d0,0.d0,0.d0,0.d0,0.d0,0.1d0,0.1d0,0.1d0/)

!    type(T_object_state) XST

     type(T_SAT_ICS), pointer :: pICS      
     real*8 :: rot_ant2loc(3,3) =(/1.d0,0.d0,0.d0,0.d0,1.d0,0.d0,0.d0,0.d0,1.d0/)  ! from antenna system to local system (ENU/SCF)
                                       ! antenna 
     type(T_ANT_PCV), pointer :: pPCV    
     type(T_clock):: CLK
     type(T_trop)  TROP
     real*8 :: olc(11,6)=0.d0
     integer*4 :: npar=0, ipar(maxpar_sta)=0

     !! IFB/ISB
     type(T_isb_rec)   :: ISB(maxisb)
     type(T_ifb_rec)   :: IFB(maxifb)
     integer*4        :: nISB = 0
     integer*4        :: nIFB = 0
     character        :: refSys=' '
!
!! added by ttchen for combination
!    real*8 :: dphwp(maxsat)=0.d0
   end type 

   type T_satellite
     character*20 :: anttype=' '
     character*20 :: antsnr =' '
     character(len=len_satname) :: name=' ' 
     character*2  :: skd=' ' ! dxl
     type(T_FILE) FORB       ! position-file (kin)

     integer*4 :: svn=0
     real*8 :: mass=0.d0
     real*8 :: area=0.d0
     real*8 :: x(6)=0.d0
     real*8 :: dx0(12)=(/1.d1,1.d1,1.d1,1.d1,1.d1,1.d1,1.d5,1.d5,1.d5,1.d5,1.d5,1.d5/)
!    real*8 :: wlength(5)=0.d0    ! L1, L2, LW, LN, L5
!
!! added by ttchen for combination, boundary constraint for position and
!! velocity. 
     real*8 :: Xcon=0.d-8,Vcon=1.d-8
     real*8 :: dorb(0:maxpar_sat*3)=0.d0     ! partial for position
     real*8 :: ddorb(0:maxpar_sat*3)=0.d0    ! partial for velocity
     real*8 :: xnr(12)=0.d0                  ! values  ?
     logical*4 :: lpart=.false.
     logical*4 :: lmaneuver=.false.


     real*8 :: sigr(maxfreq)=0.d0
     real*8 :: sigp(maxfreq)=0.d0
     real*8 :: sigl=0.d0

     real*8 :: rot_scf2crs(3,3)

!    type(T_object_state) XST

     integer*4 nfreq
     type(T_trans_freq) :: FREQ(10)
     
! added by xldai for satellite estimation in epoch-wise
     character*10 :: orbEst=' '
     logical*4    :: lfirst_set=.true.
     logical*4    :: leclips=.false.
     real*8       :: eclipsT=0.d0
!    real*8       :: orbq(15)=(/1.d-9,1.d-9,1.d-9,1.d-9,1.d-9,1.d-9,1.d-9,1.d-9,1.d-9,1.d-9,1.d-9,1.d-9,1.d-9,1.d-9,1.d-9/) !! orbit process constraint
     real*8       :: orbq(7)=(/1.d-12,1.d-12,1.d-12,1.d-12,1.d-12,1.d-12,1.d-16/) !! orbit process constraint acceleration in Pxyz,Vxyz,SRP
!    real*8       :: orbq_last(7)=(/1.d-12,1.d-12,1.d-12,1.d-12,1.d-12,1.d-12,1.d-16/) !! orbit process constraint acceleration in Pxyz,Vxyz,SRP
     character*3  :: orbqDir=''

     type(T_SAT_ICS), pointer :: pICS   
     type(T_ANT_PCV), pointer :: pPCV    

     type(T_clock):: CLK
     integer*4 :: npar=0, ipar(maxpar_sat)=0
   end type

end module
******************************************************/

/**
 * @M_stasat.h
 * @author Jianan Lou
 * @date 2022.7.16
 * @brief  Module M_stasat.h
 *
 *
 * @details
 * @see
 */

#ifndef _M_STASAT_H_
#define _M_STASAT_H_

#include"M_dimpar.h"
#include"M_time.h"
#include"M_file.h"
#include"M_ics.h"
#include"M_gnss_freq.h"
#include"M_isbifb.h"

//object trajectory / orbit

typedef struct
{
	T_time T;        //epoch time
	double x[9];     //position&velocity(m, m / s, m / s * *2)
	double sx[9];    //sigma
	double pd[3];    //power density
	double geo[3];   //geographical lat, lon. and height(rad, rad, m)
}T_object_state;

typedef struct
{
	char type[5] = " ";               //H / Cs / Ru
	char mode[4] = " ";               //REF, CLK
	double dclk0 = 0.0;               //Sigma0 of the initial clock offsets
	double qclk  = 0.0;               //POD of clock bias   s / square_root(s)

	int ndgr = 0;                     //degree of polynomial clock model
	//0 epochwise, 1 linear, 2 quard.
	T_time TC;
	double a[3] = { 0.0, 0.0, 0.0 }; //
	double dt = 0.0;               //correction at the epoch
	int ierr = 1;                  //= 0 available,
	double dt_cor = 0.0;
	double dt_v = 0.0;
	int icor = 1;                  //= 0 available
}T_clock;

typedef struct
{
	char ztdmod[10] = " ";
	char grdmod[10] = " ";
	char cztd[4] = " ";
	char cmap[4] = " ";
	//
	//SEA == sea - level, NOM == using nominal values, STA == at the station
	char sealoc[4] = " ";
	double p0 = 0.0, t0 = 0.0, hr0 = 0.0;
	//
	//zenith delay(total, dry, wet)
	double ztd;
	double zdd;
	double zwd;
	double dmap;
	double wmap;
	double grde_coeff;
	double grdn_coeff;
	double grde;
	double grdn;
	//
	//estimated correction
	double ztdcor = 0.0;
	//
	//statistical informaton about the process
	double dztd0 = 0.0, qztd = 0.0;
	double dgrd0 = 0.0, qgrd = 0.0;
}T_trop;

const int MAXFREQ_ANT = 30;  //igs14.atx maxfreq = 25

typedef struct
{
	char anttype[20] = " ";
	char antnum[20] = " ";
	char csvn[10] = " ";
	char cospar[10] = " ";
	char rora = ' ';
	double tbeg;      //beginning mjd
	double tend;      //end mjd
	int nfreq = 0;
	double zen1 = 0.0;
	double zen2 = 0.0;
	double dzen = 0.0;
	double dazi = 0.0;
	char cfreq[MAXFREQ_ANT][4];
	double enu[3][MAXFREQ_ANT] = { 0.0 };
	double pcv[41][301][MAXFREQ_ANT] = { 0.0 };
}T_ANT_PCV;

typedef struct
{
	T_FILE FOBS;       //obs - file
	T_FILE FORB        //orbit - file(LEO dyn), position - file(kin)
	T_FILE FATT        //attitude - file
	T_FILE FLOG        //log - file
	T_FILE FICS        //ics - file
	char name[len_staname] = "  "; 
	char name_long[len_staname] = "  "; 
	char csource[5] = "UNKN";
	char cplate[5] = "UNKN";
	char skd[2] = " ";
	double cutoff = 0.0;
	//
	//offset, from benchmark to ref.point
	char rectype[20] = " ";
	char dcbtype[10] = " ";
	char recsnr[20] = " ";
	char recfmw[20] = " ";      // receiver firmware
	char anttype[20] = " ";
	char antsnr[20] = " ";

	char csysids[10] = "  ";           //system ids from ctrl - file(G, R, C, E and their combination)
	char csysids_receiver[10] = " ";   //system ids from receiver - file

	double enu[3] = { 0.0 };

	//obs precision, pseudorange, phase, laser, kbr
	double sigr[maxfreq] = { 0.0 };
	double sigp[maxfreq] = { 0.0 };
	double sigl[maxfreq] = { 0.0 };

	//position&velocity
	double x[9] = { 0.0 };
	double geod[3] = { 0.0 };
	//double dx0[12] = {0.0};
	double dx0[12] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.1, 0.1 };

	//type(T_object_state) XST
	T_SAT_ICS *pICS;
	double rot_ant2loc[3][3] = { 1.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 1.0 };  // from antenna system to local system(ENU / SCF)
	//antenna
	T_ANT_PCV *pPCV;
	T_clock CLK;
	T_trop  TROP;
	double olc[11][6] = { 0.0 };
	int npar = 0, ipar[maxpar_sta] = { 0 };

	//IFB / ISB
	T_isb_rec  ISB[maxisb];
	T_ifb_rec  IFB[maxifb];
	int nISB = 0;
	int nIFB = 0;
	char refSys = ' ';
	//
	//added by ttchen for combination
	//real * 8 ::dphwp(maxsat) = 0.d0
}T_station;


typedef struct
{
	character * 20 ::anttype = ' '
		character * 20 ::antsnr = ' '
		character(len = len_satname) ::name = ' '
		character * 2  ::skd = ' ' // dxl
		T_FILE FORB;       // position - file(kin)

		int svn = 0;
		double mass = 0.0;
		double area = 0.0;
		double x[6] = { 0.0 };
		double dx0[12] = { 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 100000.0,100000.0,100000.0, 100000.0, 100000.0, 100000.0 };
		//real * 8 ::wlength(5) = 0.d0    !L1, L2, LW, LN, L5
		//
		//added by ttchen for combination, boundary constraint for position and
		//velocity.
		double Xcon = 10e-8, Vcon = 10e-8;
		double dorb[maxpar_sat * 3 + 1] = { 0.0 };     //partial for position
		double ddorb[maxpar_sat * 3 + 1] = { 0.0 };    //partial for velocity
		double xnr[12] = { 0.0 };                      //values ?
		bool lpart = false;
		bool lmaneuver = false;

		double sigr[maxfreq] = { 0.0 };
		double sigp[maxfreq] = { 0.0 };
		double sigl = 0.0;

		double rot_scf2crs[3][3];

		//type(T_object_state) XST

		int nfreq;
		T_trans_freq FREQ[10];

		//added by xldai for satellite estimation in epoch - wise
		char orbEst[10] = " ";
		bool lfirst_set = true;
		bool leclips = false;
		double eclipsT = 0.0;
		double orbq[15] = { 10e-9, 10e-9,10e-9, 10e-9, 10e-9, 10e-9,10e-9, 10e-9,10e-9, 10e-9, 10e-9, 10e-9, 10e-9, 10e-9, 10e-9 }; //orbit process constraint
		double orbq[7] = { 10e-12, 10e-12, 10e-12, 10e-12, 10e-12, 10e-12 ,10e-16 }; //orbit process constraint acceleration in Pxyz, Vxyz, SRP
		//double orbq_last[7] = { 10e-12, 10e-12, 10e-12, 10e-12, 10e-12, 10e-12, 10e-16 }; //orbit process constraint acceleration in Pxyz, Vxyz, SRP
		char orbqDir[3] = "";

		T_SAT_ICS *pICS;
		T_ANT_PCV *pPCV;

		T_clock CLK;
		int npar = 0;
		int ipar[maxpar_sat] = { 0 };
}T_satellite;


#endif //_M_STASAT_H_