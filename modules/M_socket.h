/******* Original Forthan code
module M_socket
  use M_dimpar

  type T_socket
     character (len=LEN_FILENAME) :: csymname=''           ! symbolic name
     character (len=LEN_FILENAME) :: coutput=''            ! output: list of CRD,TRP,SP3,CLK,..
     character (len=120)          :: cpars=''              ! srif parameters: PXSTA,..ZTDPWC,SATCLK..
     character (len=15)           :: chost='127.0.0.1'     ! host
     character (len=6)            :: cport='10000'         ! port
     integer*4                    :: iprotocol=0           ! protocol 0=UDP, 1=TCP
     logical*4                    :: lfirst=.true.         ! only for first time
     logical*4                    :: lopened=.false.       ! opened
     character (len=LEN_LONGSTR)  :: cdiscription=''       ! comments ?
  end type T_socket

  integer*4, parameter :: MAX_SOCK=12
  integer*4, save      :: nsocket = 0
  type(T_socket),save  :: TSOCKET(MAX_SOCK)

  type T_rec_bns    
    character (len=3)   :: csat         ! satellite name  G01/R01
    real*8              :: x(3)=0d0     ! x-coordinate(m)
    real*8              :: xp(3)        ! x-coordpred(m)
    real*8              :: a0           ! clock (microsec)
!
!! velocity  
    real*8              :: v(3)=0d0     ! x-velocity(m/s)     ! in SP3 it is dm/s !!!
    real*8              :: vp(3)=0d0    ! x-velocity(m/s)     ! in SP3 it is dm/s !!!
    real*8              :: a1           ! clock-rate (microsec)

    real*8              :: APC(3)=0d0   ! APC offsets in TRS [m]
    real*8              :: DCB(3)=0d0   ! PCBs, meters
    real*8              :: drel=0d0     ! 2-nd order relativistic correction (microsec)
  end type T_rec_bns     

end module M_socket
**************************************/

/**
 * @M_socket.h
 * @author Jianan Lou
 * @date 2022.7.16
 * @brief  Module M_socket.h
 *
 *
 * @details
 * @see
 */

#ifndef _M_SOCKET_H_
#define _M_SOCKET_H_

#include"M_dimpar.h"

typedef struct
{
	char csymname[LEN_FILENAME] = "";           //symbolic name
	char coutput[LEN_FILENAME] = "";            //output: list of CRD, TRP, SP3, CLK, ..
	char cpars[120] = "";                       //srif parameters : PXSTA, ..ZTDPWC, SATCLK..
	char chost[15] = "127.0.0.1";               //host
	char cport[6] = "10000";                    //port
	int iprotocol = 0;                          //protocol 0 = UDP, 1 = TCP
	bool lfirst = true;                         //only for first time
	bool lopened = false;                       //opened
	char cdiscription[LEN_LONGSTR] = "";        //comments ?
}T_socket;

const int MAX_SOCK = 12;
static int nsocket = 0;
static T_socket TSOCKET[MAX_SOCK];

typedef struct
{
	char csat[4];             //satellite name  G01 / R01
	double x[3] = { 0.0 };    //x - coordinate(m)
	double xp[3];             //x - coordpred(m)
	double a0;                //clock(microsec)
	
	// velocity  
	double v[3] = { 0.0 };    //x - velocity(m / s)     //in SP3 it is dm / s !!!
	double vp[3] = { 0.0 };   //x - velocity(m / s)     !in SP3 it is dm / s !!!
	double a1;                //clock - rate(microsec)

	double APC[3] = { 0.0 };  //APC offsets in TRS[m]
	double DCB[3] = { 0.0 };  //PCBs, meters
	double drel=0.0;          // 2-nd order relativistic correction (microsec)
}T_rec_bns;

#endif //_M_SOCKET_H_