#include"cross.h"


void cross(double*v1,double*v2,double*vout){
    double tmp[3];

    tmp[0]=v1[1]*v2[2]-v1[2]*v2[1];
    tmp[1]=v1[2]*v2[0]-v1[0]*v2[2];
    tmp[2]=v1[0]*v2[1]-v1[1]*v2[0];

    vout[0]=tmp[0];
    vout[1]=tmp[1];
    vout[2]=tmp[2];
    
    return;
 }