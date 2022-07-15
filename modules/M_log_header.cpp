#include"stdafx.h"
#include"M_log_header.h"
#include "ftool.h"

void write_log_record(FILE*lfn,T_log_record& LR){
    if(!LR.csat[0]) LR.csat[0]='G';
    if(!LR.csat[1]) LR.csat[1]='0';
    fprintf(lfn,"%3s %3s%7f%7f%4i%20.1f%20.1f",LR.cflag,LR.csat,LR.iepo,LR.jepo,LR.iflag,LR.c1,LR.c2);
    return;
}

void read_log_record(FILE*lfn,T_log_record& LR,int& ierr){
    ierr=0;
    if(fscanf(lfn,"%3s %3s%7f%7f%4i%20.1f%20.1f",&LR.cflag,&LR.csat,&LR.iepo,&LR.jepo,&LR.iflag,&LR.c1,&LR.c2)<=0){
        ierr=1;
        printf("***ERROR: read error\n");
        //handle_calltree("read_log_record","in+error_exit",true,ireturn_default);
    }
    return;
}

void write_log_header(FILE*lfn,T_log_header& HD){
    fprintf(lfn,"%26s%6d%10.3f%9d%7.2f", "%Start time and interval :",HD.T0.jd,HD.T0.sod,int(HD.seslength+0.5),HD.dintv);
    fprintf(lfn,"%26s%6d","%Max ambc in one epoch   :",HD.maxamb_epo);
    fprintf(lfn,"%26s%12d","%Old remvoed observations:",HD.nrm_old);
    fprintf(lfn,"%26s%12d","%New removed observations:",HD.nrm_new);
    fprintf(lfn,"%26s%12d","%Existed    ambiguities  :",HD.namb_old);
    fprintf(lfn,"%26s%12d","%New    ambiguities      :",HD.namb_new);
    fprintf(lfn,"%26s%12d","%Available observations  :",HD.nobs);
    fprintf(lfn,"%14s","%End of header");
};

void read_log_header(FILE*lfn,T_log_header& HD){
    int i=0,j=0,error=0;
    char line[1024];
    char substr[100]; //Intercept the remaining string
    memset(line,0,sizeof(line));
    memset(substr,0,sizeof(substr));
    for( j=0;j<8;j++){
        fgets(line, sizeof(line), lfn);
        if(strstr(line,"%End of header")) break;
        i=index_(line,':');
        if(i==0||i>1024) error=1;
        strncpy(substr,line+i,100);
        switch(j){
            case 0:
                if(!sscanf(substr, "%d %lf %lf %lf", &HD.T0.jd, &HD.T0.sod, &HD.seslength, &HD.dintv))error=1;
                break;
            case 1:
                if(!sscanf(substr,"%d",&HD.maxamb_epo))error=1;
                break;
            case 2:
                if(!sscanf(substr,"%d",&HD.nrm_old))error=1;
                break;
            case 3:
                if(!sscanf(substr,"%d",&HD.nrm_new))error=1;
                break;
            case 4:
                if(!sscanf(substr,"%d",&HD.namb_old))error=1;
                break;
            case 5:
                if(!sscanf(substr,"%d",&HD.namb_new))error=1;
                break;
            case 6:
                if(!sscanf(substr,"%d",&HD.nobs))error=1;
                break;
            default:
                break;
        } ;    
        memset(line,0,sizeof(line));
        memset(substr,0,sizeof(substr));
    } 
    if(error==1){
        printf("***ERROR(read_log_header): read file\n");
        printf("%s\n",line);   
        //call handle_calltree("read_log_header","in+error_exit",true,ireturn_default);
    }
    return;
}