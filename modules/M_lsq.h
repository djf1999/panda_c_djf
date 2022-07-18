/******* Original Forthan code
module M_lsq
integer * 4, parameter::maxpar_sbp = 200
type T_lsq
integer * 4 ::npar = 0
integer * 4 ::nobs = 0
integer * 4 ::nobs_del = 0
real * 8 ::ltpl = 0.d0
real * 8 ::sigma = 0.d0
real * 8 ::para(maxpar_sbp) = 0.d0
real * 8 ::varpar(maxpar_sbp) = 0.d0
real * 8 ::anor(maxpar_sbp*maxpar_sbp) = 0.d0
real * 8 ::bnor(maxpar_sbp)
end type

contains
logical * 4 function l_init_lsq(LE)
type(T_lsq) LE

LE%npar = 0
LE%nobs = 0
LE%nobs_del = 0
LE%ltpl = 0.d0
LE%sigma = 0.d0
LE%para(1:maxpar_sbp) = 0.d0
LE%varpar(1:maxpar_sbp) = 0.d0
LE%anor(1:maxpar_sbp * maxpar_sbp) = 0.d0
LE%bnor(1:maxpar_sbp) = 0.d0
end function

end module M_lsq
*************/

/**
 * @M_lsq.h
 * @author Jianan Lou
 * @date 2022.7.15
 * @brief  Module M_lsq
 *
 *
 * @details
 * @see
 */

#ifndef _M_LSQ_H_
#define _M_LSQ_H_

const int maxpar_sbp = 200;

typedef struct 
{
	int npar = 0;
	int nobs = 0;
	int nobs_del = 0;
	double ltpl = 0.0;
	double sigma = 0.0;
	double para[maxpar_sbp] = { 0.0 };
    double varpar[maxpar_sbp] = { 0.0 };
	double anor[maxpar_sbp*maxpar_sbp] = { 0.0 };
	double bnor[maxpar_sbp];
}T_lsq;

#endif //_M_LSQ_H_