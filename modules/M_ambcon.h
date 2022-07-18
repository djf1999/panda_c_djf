#ifndef _M_AMBCON_H_
#define _M_AMBCON_H_

#include "M_dimpar.h"
#include "M_time.h"
#include "M_run_error.h"
#include "M_file.h"

struct T_ambcon_header
{
    T_time T0;
    double dintv;
    int nsat;
    char csat[maxant][len_satname];
    int nsite,ndef;
    char csite[maxsit][len_staname];
};

struct T_ambcon_rec
{
    char cambtype[2];
    int isite1,isite2,isat1,isat2;
    int iepo0,iepo1;
    double t0,t1;
    double nw,nn;
};

void read_ambcon_header(T_file& FAMBCON,T_ambcon_header& HD);

void read_ambcon_rec(T_file& FAMBCON,T_ambcon_header& HD,T_ambcon_rec AMB_DD[],int idef);


#endif