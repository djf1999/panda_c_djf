#include"dot.h"

// purpose  : dot product of two vectors
//
// parameter: n -- dimmesion of vectors
//             v1, v2 -- input vecotrs
//             dot -- dot product of v1 and v2
//
// author   : Ge Maorong
//
// last mod.: 31-May-2003 by Maorong GE, CLEAN 

double dot_(int n,double v1[],double v2[]){
    int i=0;
    double result=0.0;

    for(i=0;i<n;i++)
        result+=v1[i]*v2[i];
    
    return result;
}