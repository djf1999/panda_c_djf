#ifndef _M_ESTIMATOR_H_
#define _M_ESTIMATOR_H_

#include "M_dimpar.h"

// estimator
struct T_LSQ_INFO{
    int ntot;        // total number of parameters active in NEQ
    int np;          // number of pure white-noise parameters
    int nx;          // number of constant paramters

    int nepo ;       // epoch counter
    int nepo_obs ;       // epoch counter
    int nobs_tot;    // total number of observations
    int npar_tot;    // including  all eliminated parameters

    int nobs;          // number of obs. of this batch/epoch

    double ltpl;
    double sigma0;

    union {
    
        int ndim_neq;           // allocated dimension for NEQ
        int ndim_par;           // allocated dimension for PAR
        int ndim_par_actual;    // number of parameters (process parameters counted only once
                                          // all compacted once are counted 

        int ndim;          // allocated dimension
        int mamb;          // max. number of ambiguities at epochs
        int mobs;          // max. number of observations at epochs
    };
    T_LSQ_INFO (){
        ntot=0;
        np=0;          // number of pure white-noise parameters
        nx=0;          // number of constant paramters

        nepo=0;        // epoch counter
        nepo_obs=0;    // epoch counter
        nobs_tot=0;    // total number of observations
        npar_tot=0;    // including  all eliminated parameters

        nobs=0;        // number of obs. of this batch/epoch

        ltpl=0.0;
        sigma0=0.0;

        ndim_neq=0;
        ndim_par=0;
        ndim_par_actual=0;
        ndim=0;
        mamb=0;
        mobs=0;
    }
};

struct T_SquareRootInfo_Filter{
    T_LSQ_INFO INFO;
    
    int* iptx;           // index of the last element in (i-1)-th raw
    int** index_obs;        
                         // so that the index for (i,j) is iptx(i)+j

    double postfit_rms;  // post fit rms at the epoch
    double resmax;       // max. residuals at the epoch

    double* ry;          // square root information
    double* sigobs;      // STD of obs. for QC

    double** s;          // square root information

    double** sen;

};

struct T_LSQ_Estimator{
    T_LSQ_INFO INFO;
    bool linv;
    bool l2dim;
    int* iptx;    
    double* neq;                  // NEQ 
    double* w;                    // W 
    
    T_LSQ_Estimator(){
        linv=false;
        l2dim=false;
    }
};

struct T_SquareRootInfo_Filter{
    T_LSQ_INFO INFO;
    
    int*  iptx;            // index of the last element in (i-1)-th raw
    int** index_obs;
                                       // so that the index for (i,j) is iptx(i)+j

    double  postfit_rms;   // post fit rms at the epoch
    double  resmax;        // max. residuals at the epoch

    double*  ry;           // square root information
    double*  sigobs;       // STD of obs. for QC

    double** s;            // square root information

    double** sen;

};

struct T_Parameter{
    bool l_rm;                          //be removed if it is not active
    char name[len_parname];              //name    
    int isat;                 //index of satellite
    int ista;                 //index of station   
    int nobs;
    double time[3];                      
    double elev[3];
    double azim[3];
    double xini,  sxini;
    double xest,  sxest;
    double xpred, sxpred;

//state constraints
    int nmap;
    double* map;         // state map-matrix
    double* pw;          // LSQ weight of state-equations, 
                                          // SRIF SRI of state-equaitons (Rw)
    double* rwmap;       // for SRIF only, Rw * Map

    T_Parameter(){
        for (int i=0;i<3;i++){
            time[i]=0.0; elev[i]=0.0; azim[i]=0.0;
        }
        l_rm=false;
        memset(name,0,len_parname);
        isat=0;
        ista=0;
        nobs=0;
        xini=0.0,sxini=1e20;
        xest=0.0,sxest=1e20;
        xpred=0.0,sxpred=1e20;
        nmap=0;
    };
};

//allocation of dynamic memory
void l_allocate_lsq(T_LSQ_Estimator b);

//allocation of dynamic memory
void l_deallocate_lsq(T_LSQ_Estimator b);

//allocation of dynamic memory
void l_allocate_srif(bool l_qc,T_SquareRootInfo_Filter b);

//allocate state-equations
void allocate_map(T_Parameter PAR)

#endif