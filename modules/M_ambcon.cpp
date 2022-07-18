#include"M_ambcon.h"

void read_ambcon_header(T_file& FAMBCON,T_ambcon_header& HD){
    const char cprogname[]="read_ambcon_header";

    bool lreturn;
    char cline[128];
    int nleft,i;
    bool error=false;

    // function called
    int get_valid_unit;

    //call handle_calltree(cprogname,'in',TTREE%ldebug,ireturn_default)

    if(!FAMBCON.lopened) lreturn=lopenfile(FAMBCON,true) ;

    if(fgets(cline,sizeof(cline),FAMBCON.iunit)!=NULL) error=true;
    if(fgets(cline,sizeof(cline),FAMBCON.iunit)!=NULL) error=true;
    if(fscanf(FAMBCON.iunit,"%d%lf%d%lf",&HD.T0.jd,HD.T0.sod,HD.dintv,HD.nsat,HD.nsite,HD.ndef)<=0) error=true;
    for (i=0;i<HD.nsat;i++)
        if(fscanf(FAMBCON.iunit,"%s",&HD.csat[i])<=0)
            error=true;

    for (i=0;i<HD.nsite;i++)
        if(fscanf(FAMBCON.iunit,"%s",&HD.csite[i])<=0)
            error=true;

    printf("ambiguity constraint file used, %s",FAMBCON.name);
    //call handle_calltree(cprogname,"out",TTREE%ldebug,ireturn_default)
    if(error==true){
        printf("***ERROR: read header of file: %s",FAMBCON.name);
        //call handle_calltree(cprogname,'error_exit',.true.,ireturn_default)
    }
    else{
         printf("ambiguity constraint file used, %s",FAMBCON.name);
    //call handle_calltree(cprogname,"out",TTREE%ldebug,ireturn_default)
    }
    return;
}

void read_ambcon_rec(T_file& FAMBCON,T_ambcon_header& HD,T_ambcon_rec AMB_DD[],int idef){
    const char cprogname[]="read_ambcon_rec";

    bool lreturn,error=false;
    char cline[128],tmp_char;
    char cambtype[2],str_cmp[4];
    bool error=false;
    int str_length;

    T_time TB,TE;
    int i,idx[6];
    double xdd[5];

    //call handle_calltree(cprogname,"in",TTREE%ldebug,ireturn_default)
    while(fgets(cline,sizeof(cline),FAMBCON.iunit)){
        strncpy(str_cmp,cline,4);
        if(strcmp(str_cmp, "EOF")) break;
        if(!cline[0])continue;

        idef+=1;

        if(sscanf(cline, "%c %s %d %d %d %d %d %d %lf %lf %lf %lf %lf", &tmp_char,cambtype,&idx[0],&idx[1],&idx[2],
        &idx[3],&idx[4],&idx[5],&xdd[0], &xdd[1],&xdd[2],&xdd[3],&xdd[4])<=0) error=true;

        timeinc(HD.T0,(idx[4]-1.0)*HD.dintv+HD.dintv*0.1,TB);
        timeinc(HD.T0,(idx[5]-1.0)*HD.dintv-HD.dintv*0.1,TE);

        strcpy(AMB_DD[idef].cambtype,cambtype);
        AMB_DD[idef].t0=time2fjd(TB);
        AMB_DD[idef].t1=time2fjd(TE);
    
      // check number of added contraints
        AMB_DD[idef].iepo0=idx[4];
        AMB_DD[idef].iepo1=idx[5];
        AMB_DD[idef].nw=xdd[0];
        AMB_DD[idef].nn=xdd[2];
        AMB_DD[idef].isite1=idx[0];
        AMB_DD[idef].isat1=idx[1];
        AMB_DD[idef].isite2=idx[2];
        AMB_DD[idef].isat2=idx[3];
    }
    
    if(error==true){
        printf("***ERROR: read record of file: %s",FAMBCON.name);
        //call handle_calltree(cprogname,'error_exit',.true.,ireturn_default)
    }
    else{
         printf("ambiguity constraint file used, %s",FAMBCON.name);
        //call handle_calltree(cprogname,'out',TTREE%ldebug,ireturn_default)
    }

    return;
}

