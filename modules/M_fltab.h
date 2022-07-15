#ifndef _M_FLTAB_H_
#define _M_FLTAB_H_
#include "M_dimpar.h"

const int maxfile=100;
//
// empty type means default
const char* ctype_default = "Processing Files";


struct T_fltab{
    bool lfirst;
    bool l_fform_t;
    int ntotal;
    int nfile[3];
    char ctypes[3][30];
    char fname[maxfile][20];
    char fform[maxfile][256];
    char fform_t[maxfile][256];
    T_fltab(){
        lfirst=true;
        l_fform_t=false;
        ntotal=0;
        nfile[0]=0;nfile[1]=0;nfile[2]=0;
        strcpy(ctypes[0],"System Files");
        strcpy(ctypes[1],"Source Files");
        strcpy(ctypes[2],"Processing Files");
    }
};

#endif