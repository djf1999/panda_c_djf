#ifndef _M_INTEGRATOR_H_
#define _M_INTEGRATOR_H_

// integrator coefficients of runge-kutta method
struct T_rkf_coefficient{
    int     m;
    double  alpha[10];
    double  beta[10][10];
    double  c[10];
    double  d[10];
};

// integrator coefficients of adams method
struct T_adams_coefficient{
    int     n;
    double  beta[21];
    double  beta1[21];
};

void rkf_coeff(T_rkf_coefficient& RKFC);

void adams_coeff(T_adams_coefficient& AC);

#endif