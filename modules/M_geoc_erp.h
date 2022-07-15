#ifndef _M_GEOC_ERP_H_
#define _M_GEOC_ERP_H_

#include"M_dimpar.h"

const int max_geoc_erp=10;

struct T_erp_init{
    double pole_ini[4];
    double dpole_ini[4];
    double tref;
    double tstart;
    double tend;
    T_erp_init(){
        pole_ini[0]=0;pole_ini[1]=0;pole_ini[2]=0;pole_ini[3]=0;
        dpole_ini[0]=0;dpole_ini[1]=0;dpole_ini[2]=0;dpole_ini[3]=0;
        tref=0;
        tstart=0;
        tend=0;
    }
};

struct T_geoc_erp{
    int        npar;
    char       estmod[4];
    char       cpar[max_geoc_erp][len_parname];
    int        dpole_index[4];
    double     xini[max_geoc_erp];
    int        nErpInit;
    T_erp_init erpInit[max_geoc_erp];
//   real*8 :: pole_ini(4) = 0.d0
//   real*8 :: dpole_ini(4) = 0.d0
//   real*8 :: erp_tref = 0.d0
    double sxini[max_geoc_erp];
    double sparam[max_geoc_erp];
    T_geoc_erp(){
        npar=0;
        memset(dpole_index,0,4*sizeof(int));
        nErpInit=0;
    };
};

struct T_eop_hd{       
    char      cver[10];                      // old or new
    char      ctype[4];                      // ut1 type
    char      cfmt[120];                     // format 
    int       mjdbeg,mjdend;                 // start/end mjd 
    int       nvar;                          // nubmer of varialbes
    double    dintv;                         // table interval in days
    double    unit[10];                      // units

    int       npnt_inline;                   // number of records per line (this is only used by the old format)
    char      comments[4][256];    
    T_eop_hd(){
        strcpy(ctype,"UT1R");
    }
};

struct T_bulletin_a_rec{
    double rmjd;
    double xpole, ypole, sxpole, sypole;
    double dxpole, dypole, sdxpole, sdypole;
    double ut1,   dut1,  sut1,   sdut1;
    double dpsi,  depsi, sdpsi,  sdepsi;
    double lod, ut1_utc;
    char   cid_pole;
    char   cid_ut1;
    char   cid_nut;

    char   cid_e_pole;
    char   cid_e_ut1 ;
    char   cid_e_nut ;
    T_bulletin_a_rec(){
        cid_pole='-';
        cid_ut1='-';
        cid_nut='_';
        cid_e_pole='-';
        cid_e_ut1 ='-';
        cid_e_nut ='-';
    }
};

struct T_bulletin_a{
    int   nrec;
    int   ilast_pole_estimated;
    int   ilast_ut1_estimated;
    int   ilast_nut_estimated;
    T_bulletin_a_rec* REC;
    T_bulletin_a(){
        nrec=0;
        ilast_pole_estimated=0;
        ilast_ut1_estimated=0;
        ilast_nut_estimated=0;
    }
};

void l_int_eoprec(T_bulletin_a_rec& REC);

bool l_alloc_bulletin(T_bulletin_a& TBA);


#endif