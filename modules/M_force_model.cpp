#include "M_force_model.h"
#include "ftool.h"

bool l_orbit_parameter(char* cparname,int& length){
    int length;
    bool l_orbit_parameter_=false;
    char dest1[len_parname],dest2[len_parname];

    int i,j;
    if(strlen(cparname)==0){
        printf("***WARNING: parameter name is empty\n ");
        return l_orbit_parameter_;
    }
    //
    //// name without splitting information
    i=index_(cparname,':')-1;
    if(i==-1) i=strlen(cparname);
    length=i;
    //
    //// check if it is one of Pos&Vel parameters
    for(j=0;j<6;j++){
        strncpy(dest1,cparname,i);
        strcpy(dest2,cposvel[j]);
        //linux
        if(strcasecmp(Trim(dest2),Trim(dest1)))continue;
        l_orbit_parameter_=true;
        break;
    }
    //
    //// other force model parameters
    for(j=0;j<max_force_param;j++){
        strncpy(dest1,cparname,i);
        strcpy(dest2,param_all[j]);
        //linux
        if(strcasecmp(Trim(dest2),Trim(dest1)))continue;
        l_orbit_parameter_=true;
        break;
    } 

    return l_orbit_parameter_;

}