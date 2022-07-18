/******* Original Forthan code
module M_residuals 
  use M_dimpar
  use M_time
  use M_run_error
  use M_file

  type T_resid_header
    type(T_time) T0
    integer*4 nsat,nsite,nepo
    character(len=len_satname) csat(maxsat)
    integer*4 nobs_tot
    integer*4 npar_tot
    real*8    dintv,sigma0
    character(len=len_staname) csite(maxsit) 
    integer*4 nobstype
    character(len=4) obstype(maxtype)
  end type

  type T_resid
    type(T_file) FLOG
    integer*4, allocatable :: resl3(:,:)
    integer*4, allocatable :: resp3(:,:)
    integer*4, allocatable :: iamb(:,:)
    real*4,    allocatable :: elev(:,:)
    real*4,    allocatable :: azim(:,:)
    real*4,    allocatable :: std (:,:)
    real*4,    allocatable :: wmap(:,:)
    real*4,    allocatable :: dmap(:,:)
  end type

  contains 

  logical*4 function l_allocate_resid(ltrop,nepo,nsat,R)
  logical*4 ltrop
  integer*4 nsat,nepo
  type(T_resid) R

  integer*4 :: ierr=0,ierr1=0

  allocate(R%resl3(nepo,nsat),R%resp3(nepo,nsat),R%elev(nepo,nsat),R%iamb(nepo,nsat),R%azim(nepo,nsat),stat=ierr)
  if(ltrop) allocate(R%std(nepo,nsat),R%wmap(nepo,nsat),R%dmap(nepo,nsat),stat=ierr1)
  l_allocate_resid=ierr.eq.0.and.ierr1.eq.0
  if(.not.l_allocate_resid) return

  R%resl3(1:nepo,1:nsat)=0
  R%resp3(1:nepo,1:nsat)=0
  R%elev (1:nepo,1:nsat)=0.
  R%iamb (1:nepo,1:nsat)=9     ! not date
  R%azim (1:nepo,1:nsat)=0.
  if(ltrop) then
    R%std  (1:nepo,1:nsat)=0.
    R%wmap (1:nepo,1:nsat)=0.
    R%dmap (1:nepo,1:nsat)=0.
  endif

  return
  end function

  logical*4 function l_deallocate_resid(ltrop,R)
  logical*4 ltrop
  type(T_resid) R

  integer*4 :: ierr=0,ierr1=0

  deallocate(R%resl3,R%resp3,R%elev,R%iamb,R%azim,stat=ierr)
  if(ltrop) deallocate(R%std,R%wmap,R%dmap,stat=ierr1)
  l_deallocate_resid=ierr.eq.0.and.ierr1.eq.0
  
  return
  end function


  subroutine write_resid_header(lfn,HD)
  implicit none
  integer*4 lfn
  type(T_resid_header) HD
  write(lfn,'(a,i6,2f15.5)')  'Time&Interval : ',HD%T0%jd,HD%T0%sod,HD%dintv
  write(lfn,'(a,i4,i5,i8)')        'Total number of satellites and stations: ',HD%nsat,HD%nsite,HD%nepo
  write(lfn,'(a,f10.3)')      'Sigma : ', HD%sigma0
  write(lfn,'(a,i20)')        'Total number of estimated parameters: ', HD%npar_tot
  write(lfn,'(a,i20)')        'Total number of observations: ', HD%nobs_tot
  write(lfn,'(a,i4,10(1x,a4))') 'Observation type : ',HD%nobstype,HD%obstype(1:HD%nobstype)
  write(lfn,'(20(4hSAT:,25(1x,a3)/))')  HD%csat(1:HD%nsat)
  write(lfn,'(20(4hSTA:,20(1x,a4)/))') HD%csite(1:HD%nsite)
  end subroutine

  subroutine is_res_file(lfn,lres)
  implicit none
  integer*4 lfn
  logical*4 lres

  character(len=256) cline

  read(lfn,'(a)',err=100) cline
 
  lres=index(cline,'Time&Interval :').ne.0
  return

100 lres=.false.

  return
  end subroutine

  subroutine read_resid_header(lfn,HD)
  implicit none
  integer*4 lfn
  type(T_resid_header) HD 
  integer*4 i,j
  character(len=256) line

  do j=1,6
    read(lfn,'(a)',err=100) line
    i=index(line,':')
    if(i.eq.0) goto 100
    if(j.eq.1) read(line(i+1:),*,err=100) HD%T0%jd,HD%T0%sod,HD%dintv
    if(j.eq.2) read(line(i+1:),*,err=100) HD%nsat,HD%nsite,HD%nepo
    if(j.eq.3) read(line(i+1:),*,err=100) HD%sigma0
    if(j.eq.4) read(line(i+1:),*,err=100) HD%npar_tot
    if(j.eq.5) read(line(i+1:),*,err=100) HD%nobs_tot
    if(j.eq.6) read(line(i+1:),*,err=100) HD%nobstype,HD%obstype(1:HD%nobstype)
  enddo
  read(lfn,'(20(4x,25(1x,a3)/))') HD%csat(1:HD%nsat)

  read(lfn,'(20(4x,20(1x,a4)/))') HD%csite(1:HD%nsite)
  return
100 write(*,*) '***ERROR: read file'
  call handle_calltree('read_resid_header','in+error_exit',.true.,ireturn_default)
  end subroutine

end module
************************************/


/**
 * @M_residuals.h
 * @author Jianan Lou
 * @date 2022.7.16
 * @brief  Module M_residuals
 *
 *
 * @details
 * @see
 */

#ifndef _M_RESIDUALS_H_
#define _M_RESIDUALS_H_

#inlcude"M_dimpar.h"
#include"M_time.h"
#include"M_run_error.h"
#include"M_file.h"

typedef struct
{
	T_time T0;
	int nsat, nsite, nepo;
	char csat[maxsast][len_satname];
	int nobs_tot;
	int npar_tot;
	double dintv, sigma0;
	char csite[maxsit][len_staname];
	int nobstype;
	char obstype[maxtype][4];
}T_resid_header;

typedef struct
{
	T_file FLOG;
	int **resl3;
	int **resp3;
	int **iamb;
	float **elev;
	float **azim;
	float **std;
	float **wmap;
	float **dmap;
}T_resid;


#endif //_M_RESIDUALS_H_