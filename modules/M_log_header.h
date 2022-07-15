#ifndef _M_lOG_HEADER_H_
#define _M_lOG_HEADER_H_

#include "M_dimpar.h"
#include "M_time.h"
#incldue "M_run_error.h"

struct T_log_header{
    T_time T0;
    double seslength;
    double dintv;
    int maxamb_epo;
    int nrm_old;
    int nrm_new;
    int namb_old;
    int namb_new;
    int nobs;
    T_log_header ():seslength(0.0),dintv(0.0),maxamb_epo(0),nrm_old(0),nrm_new(0),namb_new(0),
    namb_old(0),nobs(0){};
};

struct T_log_record{
    char  cflag[3];
    char  csat[len_satname];
    int        iepo;
    int        jepo;
    int        iflag;
    double     c1,c2;
    T_log_record(){
        memset(cflag,0,3);
        memset(csat,0,len_satname);
    }
};

void write_log_record(FILE*lfn,T_log_record& LR);

void read_log_record(FILE*lfn,T_log_record& LR,int& ierr);

void read_log_header(FILE*lfn,T_log_header& HD);

void write_log_header(FILE*lfn,T_log_header&HD);

#endif