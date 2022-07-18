#include "matmpy.h"
#include "dot.h"

void matmpy(double** A,double**B,double**C,int nrow,int ncola,int ncolb){
    int i,j,k=0;
    double c1[nrow][ncolb],B_tmp[ncola];

    for(i=0;i<nrow;i++){
        for(j=0;j<ncolb;j++){
            for(k=0;k<ncola;k++)  
                B_tmp[k]=B[k][j];
            c1[i][j] = dot_(ncola,A[i],B_tmp);
        }
    }
    for(i=0;i<nrow;i++)
        for(j=0;j<ncolb;j++)
            C[i][j]=c1[i][j];
    return;
}