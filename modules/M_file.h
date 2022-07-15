#ifndef _M_FILE_H_
#define _M_FILE_H_

#include "M_dimpar.h"
#include "M_run_error.h"

struct T_file
{
    int iunit;
    char name[len_filename];

    //as input parameters for lopenfile ??
    char form[20];
    char status[20];
    int  irec_length;
    int  ioerr;
    int  irec;

    bool lopened;
    char cinfo[len_longstr];
    T_file()
    {
        iunit=0;
        memset(name,0,len_filename);
        strcpy(form,"FORMATTED");
        strcpy(status,"UNKNOWN");
        irec_length=99999;
        ioerr=0;
        irec=0;
        lopened=false;
        memset(cinfo,0,len_filename);
    };
};

bool lopenfile (T_file& F, bool& lstop);

bool ldeletfile(const char* fname);

bool lexistfile(const char* fname);

bool isizeoffile(const char* fname);


#endif