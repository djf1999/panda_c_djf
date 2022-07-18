#include"M_file.h"
#include"stdafx.h"
#include "M_file.h"
#include "M_run_error.h"

bool lopenfile (T_file& F, bool lstop)
{
    char cprogname[10]="lopenfile";
    char cwarn[10];
    bool res_flag=false,ioerr=false;

    //functions called
    //handle_calltree(cprogname,"in",TTREE.ldebug,ireturn_default);

    if(lstop)
        strcpy(cwarn,"***ERROR");
    else
        strcpy(cwarn,"**WARNING");
    
    if(strlen(F.name)==0)
        printf("%c: file name is empty.\n",cwarn);
    //if(lstop) handle_calltree(cprogname,"error_exit",true,ireturn_default);
    //F.iunit = get_valid_unit(10);
    // strcpy(F.form,upper_string(F.form));
    if(!strcmp(F.form,"UNFORMATTED")){
        if((F.iunit=fopen(F.name,F.status))==NULL)
        ioerr=true;//Binary file read or write default:"w+"
    }
    else{
        F.iunit=fopen(F.name,F.status);//txt file
        ioerr=true;
    }
    if (F.ioerr!=true){
        printf("%c : open file : %s\n",cwarn,F.name);
        printf(" status= %s\n",F.status);
        if(!strcmp(F.form,"UNFORMATTED"))printf(" recl= %d\n",F.irec_length);
        printf("file info:\n %s\n",F.cinfo);
        //if(lstop) handle_calltree(cprogname,"error_exit",true,ireturn_default);
        F.lopened=ioerr;
    }
    return ioerr;
}
bool lclosefile (T_file& F,char* cstatus, bool lstop){
    char cprogname[12]="lclosefile";

    int ierr=0;
    char cwarn[10];
    if(lstop){
        strcpy(cwarn,"***ERROR");
        strcpy(cwarn,"**WARNING");
    }

    fclose(F.iunit);

    if(!ierr){
        printf("%s : close file \n",F.name);
        printf("status= %s iostat= %d\n",cstatus,ierr);
        //if(lstop)  handle_calltree(cprogname,"in+error_exit",true,ireturn_default)
        F.lopened= false;
    }
    return true;
}

bool ldeletfile(const char* fname){
    char cprogname[12]="lclosefile";
    char *fname;

    bool lexlist;
    T_file FTMP;
    FILE* tmp_fl;
    
    strcpy(FTMP.name,fname);
    strcpy(FTMP.status,"r");

    if(!access(FTMP.name,F_OK)){
        tmp_fl=fopen(FTMP.name,FTMP.status);
        if(!fclose(tmp_fl)) remove(FTMP.name);
        return true;
    }
    return false;
}

bool lexistfile(const char* fname){
    char cprogname[12]="lexistfile";
    if(!access(fname,F_OK))
        return true;
    else
        return false;
};

int isizeoffile(const char* fname){
    int res_size=-1;
    struct stat statbuf;
    if(access(fname,F_OK)){
        printf("***WARING(isizeoffile): cannot open file %s\n",fname);
    }
    else{
        stat(fname,&statbuf);
        res_size=statbuf.st_size;
    }
    return res_size;
}