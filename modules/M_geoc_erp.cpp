#include "stdafx.h"
#include"M_geoc_erp.h"

void l_int_eoprec(T_bulletin_a_rec& REC){

    REC.rmjd   = 0;
    REC.xpole  = 0.0;
    REC.ypole  = 0.0;
    REC.ut1    = 0.0;     
    REC.dut1   = 0.0;     
    REC.dpsi   = 0.0;
    REC.depsi  = 0.0;
    REC.sxpole = 0.0;
    REC.sypole = 0.0;
    REC.sut1   = 0.0;        
    REC.sdut1  = 0.0 ;    
    REC.sdpsi  = 0.0;
    REC.sdepsi = 0.0;
    REC.lod = 0.0;
    REC.ut1_utc = 0.0;
    REC.dxpole  = 0.0;
    REC.dypole  = 0.0;
    REC.sdxpole  = 0.0;
    REC.sdypole  = 0.0;

    REC.cid_pole='-';
    REC.cid_ut1 ='-';
    REC.cid_nut ='-';
    REC.cid_e_pole='-';
    REC.cid_e_ut1 ='-';
    REC.cid_e_nut ='-';

    return;
}

bool l_alloc_bulletin(T_bulletin_a& TBA){
    int ierr;
    bool l_alloc_bulletin_=false;
    //allocate(TBA%REC(1:TBA%nrec),stat=ierr)
    
    TBA.REC=(T_bulletin_a_rec*)malloc(sizeof(T_bulletin_a_rec)*TBA.nrec);
    if(TBA.REC!=NULL) l_alloc_bulletin_=true;

    return l_alloc_bulletin_;
}

bool l_dealloc_bulletin(T_bulletin_a& TBA){

    int ierr;

    free(TBA.REC);
    TBA.REC=NULL;
    return true;
}