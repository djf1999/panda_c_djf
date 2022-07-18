/******* Original Forthan code
module M_pre_residuals
   use M_dimpar
   use M_time 
   use M_file

!! priori residuals
  type T_pre_residuals
    integer*4    :: isit = 0
    integer*4    :: isat = 0
    integer*4    :: iepo = 0
    type(T_time) :: T 
    character(len=len_staname) :: siteName = ''
    character(len=len_satname) :: satName = ''
    real*8       :: omc = 0.d0
    real*8       :: res=0.d0
    real*8       :: srif_res = 0.d0
    real*8       :: wgt = 0.d0
  end type T_pre_residuals
  
end module
***************************/

/**
 * @M_pre_residuals.h
 * @author Jianan Lou
 * @date 2022.7.16
 * @brief  Module M_pre_residuals
 *
 *
 * @details
 * @see
 */

#ifndef _M_PRE_RESIDUALS_H_
#define _M_PRE_RESIDUALS_H_

#include"M_dimpar.h"
#include"M_time.h"
#include"M_file.h"

// priori residuals
typedef struct
 {
	int isit = 0;
	int isat = 0;
	int iepo = 0;
	T_time T;
	char siteName[len_staname] = "";
	char satName[len_staname] = "";
	double omc = 0.0;
	double res = 0.0;
	double srif_res = 0.0;
	double wgt = 0.0;

 }T_pre_residuals;


#endif //_M_PRE_RESIDUALS_H_