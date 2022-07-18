#include "M_estimator.h"
#include "stdafx.h"

bool l_allocate_lsq(T_LSQ_Estimator& b){
    bool l_allocate_lsq_=false;
    int  ndim;
    int  i;
    ndim=b.INFO.ndim_neq;
    //allocate (b%iptx(1:ndim),b%neq(1:ndim*ndim),b%w(1:ndim),stat=ierr)

    b.iptx=(int*)malloc(sizeof(int)*ndim);
    b.neq=(double*)malloc(sizeof(double)*ndim*ndim);
    b.w=(double*)malloc(sizeof(double)*ndim);

    if((b.iptx!=NULL)&&(b.neq!=NULL)&&(b.w!=NULL)){
        memset(b.neq,0,sizeof(double)*ndim*ndim);
        memset(b.w,0,sizeof(double)*ndim);
        for (i=0;i<ndim;i++) b.iptx[i]=(i+1)*i/2;
        l_allocate_lsq_=true;
    }
    return l_allocate_lsq_;   
};

bool l_deallocate_lsq(T_LSQ_Estimator& b){
    bool l_deallocate_lsq_=false;
    free(b.neq);
    free(b.w);
    free(b.iptx);
    b.neq=NULL;
    b.iptx=NULL;
    b.w=NULL;
    if((b.neq==NULL)&&(b.w==NULL)&&(b.iptx=NULL))
        l_deallocate_lsq_=true;
    return l_deallocate_lsq_;
}

bool l_allocate_srif(bool& l_qc,T_SquareRootInfo_Filter& b){
    bool l_allocate_srif_=false;
    int  ndim;
    int  nele,i;

    ndim=b.INFO.ndim;
    nele=(ndim+2)*(ndim+1)/2;


    b.s=(double**)malloc((b.INFO.np+ndim+1)*sizeof(double*));
    for(i=0;i<b.INFO.np+ndim+1;i++) b.s[i]=(double*)malloc((b.INFO.np+ndim+1)*sizeof(double));

    b.ry=(double*)malloc(nele*sizeof(double));

    b.sigobs=(double*)malloc(sizeof(double)*b.INFO.mobs*2);

    b.index_obs=(int**)malloc(b.INFO.mobs*2*sizeof(int*));
    for(i=0;i<b.INFO.mobs*2;i++) b.index_obs[i]=(int*)malloc(4*sizeof(int));

    b.iptx=(int*)malloc(ndim*sizeof(int));
    
    if((b.s!=NULL)&&(b.ry!=NULL)&&(b.sigobs!=NULL)&&(b.index_obs!=NULL)&&(b.iptx!=NULL))
        l_allocate_srif_=true;

    if(l_qc){
        b.sen=(double**)malloc((b.INFO.ndim+b.INFO.mobs*2)*sizeof(double*));
        for(i=0;i<b.INFO.ndim+b.INFO.mobs*2;i++) b.sen[i]=(double*)malloc((b.INFO.mobs*2)*sizeof(double));
        if(b.sen==NULL) l_allocate_srif_=false;
    };

    if(l_allocate_srif_==true){
        memset(b.s,0,(b.INFO.np+ndim+1)*(b.INFO.np+ndim+1)*sizeof(double));
        memset(b.ry,0,nele*nele*sizeof(double));
        memset(b.sigobs,0,sizeof(double)*b.INFO.mobs*2);
        memset(b.index_obs,0,sizeof(b.INFO.mobs*2*4*sizeof(int)));
        if(b.sen!=NULL)
            memset(b.sen,0,(b.INFO.ndim+b.INFO.mobs*2)*(b.INFO.mobs*2)*sizeof(double));
    }
    
    return l_allocate_srif_;

};

bool l_deallocate_srif(bool& l_qc,T_SquareRootInfo_Filter& b){
    bool l_deallocate_srif_=false;
    int i=0;
    int ndim,nele;

    ndim=b.INFO.ndim;
    nele=(ndim+2)*(ndim+1)/2;

    free(b.ry);
    free(b.sigobs);
    free(b.iptx);

    b.ry=NULL;
    b.sigobs=NULL;
    b.iptx=NULL;

    for(i=0;i<b.INFO.np+ndim+1;i++) free(b.s[i]);
    free(b.s);
    b.s=NULL;

    for(i=0;i<b.INFO.mobs*2;i++) free(b.index_obs[i]);
    free(b.index_obs);
    b.index_obs=NULL;

    if(l_qc){
        for(i=0;i<b.INFO.ndim+b.INFO.mobs*2;i++) free(b.sen[i]);
        free(b.sen);
        b.sen=NULL;
    }
    l_deallocate_srif_=true;
    return l_deallocate_srif_;
}

bool allocate_map(T_Parameter& PAR){
    bool allocate_map=false;
    int  n,ierr;
    n=PAR.nmap*PAR.nmap;
   // allocate(PAR%map(1:n),PAR%pw(1:n),PAR%rwmap(1:n),stat=ierr)
    PAR.map=(double*)malloc(n*sizeof(double));
    PAR.pw=(double*)malloc(n*sizeof(double));
    PAR.rwmap=(double*)malloc(n*sizeof(double));

    if((PAR.map!=NULL)&&(PAR.pw!=NULL)&&(PAR.rwmap!=NULL))
        allocate_map=true;
    memset(PAR.map,0,n*sizeof(double));
    memset(PAR.pw,0,n*sizeof(double));
    memset(PAR.rwmap,0,n*sizeof(double));
    return allocate_map;
}

void copyPar(T_Parameter&PAR,T_Parameter&PAR_tmp){
    bool  allocate_map;
    int   n,i;

    n=PAR.nmap*PAR.nmap;
    PAR_tmp.l_rm = PAR.l_rm;        // be removed if it is not active
    strcpy(PAR_tmp.name,PAR.name);   // name    
    PAR_tmp.isat=PAR.isat;              // index of satellite
    PAR_tmp.ista=PAR.ista;              // index of station   
    PAR_tmp.nobs=PAR.nobs;
    for(i=0;i<3;i++){
        PAR_tmp.time[i] = PAR.time[i];                      
        PAR_tmp.elev[i] = PAR.elev[i];
        PAR_tmp.azim[i] = PAR.azim[i];
    }
    PAR_tmp.xini=PAR.xini;
    PAR_tmp.sxini=PAR.sxini;
    PAR_tmp.xest=PAR.xest;
    PAR_tmp.sxest=PAR.sxest;
    PAR_tmp.xpred=PAR.xpred;
    PAR_tmp.sxpred=PAR.sxpred;
//
//// state constraints
    PAR_tmp.nmap=PAR.nmap;
    if(PAR.nmap>0) {
        for(i=0;i<n;i++){
            PAR_tmp.map[i]=PAR.map[i];
            PAR_tmp.pw[i]=PAR.pw[i];
            PAR_tmp.rwmap[i]=PAR.rwmap[i];
        }
    }

    return;
}