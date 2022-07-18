/******* Original Forthan code
!*
MODULE M_sinex
!!
!! Porpose    : Module of the type for sinex file.
!!
!! Restriction: ----
!!
!*
USE M_dimpar
IMPLICIT NONE

  !*
  ! sinex file head information
  !!---------------------
  TYPE SNXHEAD
    CHARACTER(3) :: doctype
	REAL*8        :: ver
	CHARACTER(3) :: file_agency,data_agency
	INTEGER      :: yr_create,doy_create,sod_create
	INTEGER      :: yr_start,doy_start,sod_start
	INTEGER      :: yr_end,doy_end,sod_end
	CHARACTER(1) :: obscode,constcode
	INTEGER      :: estnumb
	CHARACTER(12):: solcont
  END TYPE SNXHEAD

  !! SOLUTION/STATISTICS
  TYPE BK_SOL_STAT
    CHARACTER(256):: fmt
    INTEGER       :: ncnt
    CHARACTER(30) :: info_type(9)
    REAL*8         :: info_stat(9)
  END TYPE BK_SOL_STAT

!
!! SELF_DEFINE: SOLUTION/TRANSITION
  TYPE BK_SOL_TRST
    CHARACTER(256) :: fmt
    CHARACTER(3)   :: prn(maxsat)
    INTEGER        :: ncnt,nsat,jdoc
    REAL*8          :: sodoc
    CHARACTER(20)  :: typ(maxics+1,maxsat)
    REAL*8          :: val(maxvar+6,maxsat)
  END TYPE BK_SOL_TRST

!! SOLUTION/ESTIMATE and SOLUTION/APRIORI
  TYPE BK_SOL_PARA
    CHARACTER(256)   :: fmt
    INTEGER          :: nsit,nsat,neop,nics(maxsat)
!! station coordinates, GPS ics, EOP
    CHARACTER(20)         :: para_type(maxsit*3+maxics*maxsat+6)
    CHARACTER(4)          :: site_code(maxsit+maxsat)
    INTEGER               :: iysta,doysta,secsta
    INTEGER               :: iysat,doysat,secsat
    CHARACTER(1)          :: con_code(maxsit+maxics*maxsat+6)
    REAL*8                 :: para_val(maxsit*3+maxics*maxsat+6)
    REAL*8                 :: para_std(maxsit*3+maxics*maxsat+6)
    REAL*8                 :: para_atpl(maxsit*3+maxics*maxsat+6)
  END TYPE BK_SOL_PARA

!   parameter(maxpars=maxics*maxsat+3*maxsit+maxsit*maxsat*15+maxsat+maxsit+3)
!	parameter(maxpars=15000)
!! SOLUTION/MATRIX_ESTIMATE
  TYPE BK_MTX_EST
    CHARACTER(256)        :: fmt
    INTEGER               :: ncnt
    CHARACTER(1)          :: form
    CHARACTER(4)          :: cont
!        real*8 mtxcont(maxpars*(maxpars+1)/2)
    INTEGER               :: nsize
  END TYPE BK_MTX_EST   

END MODULE M_sinex
*******************************************/

/**
 * @M_sinex.h
 * @author Jianan Lou
 * @date 2022.7.16
 * @brief  Module M_sinex.h
 *
 *
 * @details
 * @see
 */

#ifndef _M_SINEX_H_
#define _M_SINEX_H_

//Porpose    : Module of the type for sinex file.
//
//Restriction : ----
//
//

#include"M_dimpar.h"
//IMPLICIT NONE

//
//sinex file head information
//-------------------- -
typedef struct
{
	char doctype[3];
	double ver;
	char file_agency[3], data_agency[3];
	int yr_create, doy_create, sod_create;
	int yr_start, doy_start, sod_start;
	int yr_end, doy_end, sod_end;
	char obscode, constcode;
	int estnumb;
	char solcont[12];
}SNXHEAD;

// SOLUTION / STATISTICS
typedef struct
{
	char fmt[256];
	int ncnt;
	char info_type[9][30];
	double info_stat[9];
}BK_SOL_STAT;

//SELF_DEFINE: SOLUTION / TRANSITION
typedef struct
{
	char fmt[256];
	char prn[maxsat][3];
	int ncnt, nsat, jdoc;
	double sodoc;
	char typ[maxics + 1][maxsat][20];
	double val[maxvar + 6][maxsat];
}BK_SOL_TRST;

//SOLUTION / ESTIMATE and SOLUTION / APRIORI

typedef struct
{
	char fmt[256];
	int nsit, nsat, neop, nics[maxsat];
	// station coordinates, GPS ics, EOP
	char para_type[maxsit * 3 + maxics * maxsat + 6][20];
	char site_code[maxsit + maxsat][4];
	int iysta, doysta, secsta;
	int iysat, doysat, secsat;
	char con_code[maxsit + maxics * maxsat + 6];
	double para_val[maxsit * 3 + maxics * maxsat + 6];
	double para_std[maxsit * 3 + maxics * maxsat + 6];
	double para_atpl[maxsit * 3 + maxics * maxsat + 6];
}BK_SOL_PARA;

//parameter(maxpars = maxics * maxsat + 3 * maxsit + maxsit * maxsat * 15 + maxsat + maxsit + 3)
//parameter(maxpars = 15000)
//SOLUTION / MATRIX_ESTIMATE

typedef struct
{
	char fmt[256];
	int ncnt;
	char form;
	char cont[5]; 
	//real * 8 mtxcont(maxpars*(maxpars + 1) / 2)
	int nsize;
}BK_MTX_EST;

#endif //_M_SINEX_H_