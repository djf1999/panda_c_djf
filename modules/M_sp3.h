/******* Original Forthan code
module M_sp3
use M_dimpar
use M_time
!
!!sp3 orbit header
integer * 4, parameter::maxsat_sp3 = 150
type T_sp3_header
character(len = 1) ::cid_vel = 'P'               !P / V
character(len = 5) ::cdata_used = 'ORBIT'        !
character(len = 5) ::cframe = 'CTS'              !
character(len = 3) ::ctype = 'UNK'               !FIT / PRE
character(len = 4) ::cproducer = 'UNKN'          !
type(T_time) TB, TE                           !start and stop time
real * 8 dintv                                  !interval in seconds
integer * 4 ::nsat = 0                         !number of satellites
character(len = len_satname) ::csat3(maxsat_sp3) = ' ' !satellite name(sp3 internal short, 3 chars)
character(len = len_satname) ::csat(maxsat_sp3) = ' ' !
integer * 4 iacc(maxsat_sp3)                    !accuracy identity
character * 1 ::csat_type = ' '                     !G / R / E / M / L / ..
end type

type T_sp3_record
type(T_time) T
integer * 4 ::nsat
character(len = len_staname) csat(maxsat_sp3)
real * 8 xpv(6, maxsat_sp3)
real * 8 xclk(2, maxsat_sp3)
integer * 4 nobs_xpv(maxsat_sp3)
integer * 4 nobs_xclk(maxsat_sp3)
end type

end module
********************************************/



/**
 * @M_sp3.h
 * @author Jianan Lou
 * @date 2022.7.16
 * @brief  Module M_sp3.h
 *
 *
 * @details
 * @see
 */

#ifndef _M_SP3_H_
#define _M_SP3_H_

#include"M_dimpar.h"
#include"M_time.h"

//sp3 orbit header
const int maxsat_sp3 = 150;

typedef struct
{
	char cid_vel = 'P';               // P / V
	char cdata_used[6]="ORBIT";       //
	char cframe[5] = "CTS";           //
	char ctype[4] = "UNK";            // FIT / PRE
	char cproducer[5] = "UNKN";       //
	T_time TB, TE;                    // start and stop time
	double dintv;                     // interval in seconds
	int nsat = 0;                     // number of satellites
	char csat3[maxsat_sp3][len_satname] = { " " }; // satellite name(sp3 internal short, 3 chars)
	char csat[maxsat_sp3][len_satname] = { " " };  //
	int  iacc[maxsat_sp3];                     // accuracy identity
	char csat_type = ' ';                      // G / R / E / M / L / ..
}T_sp3_header;

#endif //_M_SP3_H_
