#include "stdafx.h"
#include "M_args.h"
#include "M_run_error.h"

bool l_alloc_args(){

    bool l_alloc_args=true;            
    ARG=(T_ARG*)malloc(MAXARG*sizeof(T_ARG));
    memset(ARG,0,MAXARG*sizeof(T_ARG));
    if(ARG==NULL)l_alloc_args=false;
    return l_alloc_args;
}

bool l_dealloc_args(){
    bool l_dealloc_args=true;
    free(ARG);
    ARG=NULL;
    if(ARG!=NULL)l_dealloc_args=false;
    return l_dealloc_args;
}

void get_switches(int argc,char** argv){
    const char* cprogname="get_switches";

    int i,ipar,j;
    char chr;  
    char arg0[len_filename];
    char tmp_name[MAXARG][12];
    // 
    //// function called
    // char lower_string[20];
    //bool l_find_string;

    //handle_calltree(cprogname,"in",TTREE.ldebug,ireturn_default)

    narg=argc;
    //
    //// others, put leading keyword and its related values to arrays
    ipar=-1;
    for(i=1;i<narg;i++){
        strcpy(arg0,argv[i]);
        chr=lower_string(arg0[1]);
        //
        //// a switch
        if((arg0[0]=='-')&&(chr>='a')&&(chr<='z') ){
            for (j=0;j<MAXARG;j++)strcpy(tmp_name[j],ARG[i].name);
            if(!l_find_string(MAXARG,tmp_name,arg0,ipar,false)){ 
                printf("***ERROR: unknown argument : %s  try -help ",arg0);
                // handle_calltree(cprogname,"error_exit",true,ireturn_default)
            }
            memset(ARG[ipar].name,0,sizeof(ARG[ipar].name));
        }
        if(ipar<0) continue;
        ARG[ipar].npar+=1;
        strcpy(ARG[ipar].pars[ARG[ipar].npar],arg0);
    }
    //
    //// get the values
    for(ipar=0;ipar<MAXARG;ipar++){
        if(ARG[ipar].npar==0) continue;
        if(ARG[ipar].npar<ARG[ipar].nmin|| ARG[ipar].npar>ARG[ipar].nmax){
            printf("***ERROR: wrong parameters for argument : %s , try -help ",arg0);
            // handle_calltree(cprogname,'error_exit',.true.,ireturn_default)
        }
    }

    // handle_calltree(cprogname,"out",TTREE%ldebug,ireturn_default)
    return;
}