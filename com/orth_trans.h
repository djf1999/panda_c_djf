#ifndef _ORTH_H_
#define _ORTH_H_

void orth_trans(bool& lsave_u,int &ntot,int& nobs,double**s,int ndim_x,int ndim_o,int ncol);

void sens_vector(int& npar,int& nobs,double**s,int& ndim_x,int& ndim_o,int& iobs,double*w);

#endif