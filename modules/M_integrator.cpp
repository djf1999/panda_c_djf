#include "stdafx.h"
#include "M_integrator.h"

void rkf_coeff(T_rkf_coefficient& RKFC){
    int i=0,j=0;

    RKFC.m=9;
    for(i=0;i<RKFC.m+1;i++){
        RKFC.alpha[i]=0.0;
        RKFC.c[i]=0.0;
        RKFC.d[i]=0.0;
        for(j=0;j<RKFC.m;j++){
            RKFC.beta[i][j]=0.0;
        }
    }

    RKFC.alpha[1]=2.0/33.0;
    RKFC.alpha[2]=4.0/33.0;
    RKFC.alpha[3]=2.0/11.0;
    RKFC.alpha[4]=0.50;
    RKFC.alpha[5]=2.0/3.0;
    RKFC.alpha[6]=6.0/7.0;
    RKFC.alpha[7]=1.0;
    RKFC.alpha[9]=1.0;

    RKFC.beta[1][0]=2.0/33.0;
    RKFC.beta[3][0]=1.0/22.0 ;
    RKFC.beta[4][0]=43.0/64.0;
    RKFC.beta[5][0]=-2383.0/486.0;
    RKFC.beta[6][0]=10077.0/4802.0;
    RKFC.beta[7][0]=-733.0/176.0;
    RKFC.beta[8][0]=15.0/352.0;
    RKFC.beta[9][0]=-1833.0/352.0;
    RKFC.beta[2][1]=4.0/33.0;
    RKFC.beta[3][2]=3.0/22.0;
    RKFC.beta[4][2]=-165.0/64.0;
    RKFC.beta[5][2]=1067.0/54.0;
    RKFC.beta[6][2]=-5643.0/686.0;
    RKFC.beta[7][2]=141.0/8.0;
    RKFC.beta[9][2]=141.0/8.0;
    RKFC.beta[4][3]=77.0/32.0;
    RKFC.beta[5][3]=-26312.0/1701.0;
    RKFC.beta[6][3]=  116259.0/16807.0;
    RKFC.beta[7][3]=-335763.0/23296.0;
    RKFC.beta[8][3]=-5445.0/46592.0;
    RKFC.beta[9][3]=-51237.0/3584.0;
    RKFC.beta[5][4]=2176.0/1701.0;
    RKFC.beta[6][4]=-6240.0/16807.0;
    RKFC.beta[7][4]=216.0/77.0;
    RKFC.beta[8][4]=18.0/77.0;
    RKFC.beta[9][4]=18.0/7.0;
    RKFC.beta[6][5]=1053.0/2401.0;
    RKFC.beta[7][5]=-4617.0/2816.0;
    RKFC.beta[8][5]=-1215.0/5632.0;
    RKFC.beta[9][5]=-729.0/512.0;
    RKFC.beta[7][6]=7203.0/9152.0;
    RKFC.beta[8][6]=1029.0/18304.0;
    RKFC.beta[9][6]=1029.0/1408.0;
    RKFC.beta[9][8]=1.0;

    RKFC.c[0]=77.0/1440.0;
    RKFC.c[3]=1771561.0/6289920.0;
    RKFC.c[4]=32.0/105.0;
    RKFC.c[5]=243.0/2560.0;
    RKFC.c[6]=16807.0/74880.0;
    RKFC.c[7]=11.0/270.0;
            
    RKFC.d[0]=11.0/864.0;
    RKFC.d[3]=RKFC.c[3];
    RKFC.d[4]=RKFC.c[4];
    RKFC.d[5]=RKFC.c[5];
    RKFC.d[6]=RKFC.c[6];
    RKFC.d[8]=11.0/270.0;
    RKFC.d[9]=11.0/270.0;

}


void adams_coeff(T_adams_coefficient& AC)
{
    int i=0,j=0;
    double* gama,*gama1;
    double**bino;
    double s,*factor;

    gama=(double*)malloc(sizeof(double)*(AC.n+2));
    gama1=(double*)malloc(sizeof(double)*(AC.n+2));
    
    bino=(double**)malloc(sizeof(double*)*(AC.n+2));
    //Is the memory allocated too large???
    for(i=0;i<AC.n+2;i++) bino[i]=(double*)malloc(sizeof(double)*(AC.n+2));

    factor=(double*)malloc(sizeof(double)*(AC.n+2));

    //integer factor for bino. computation
    factor[0]=1.0;
    for(i=1;i<AC.n+1;i++) factor[i]=factor[i-1]*i;
    for(i=0;i<AC.n+1;i++)
        for(j=0;j<i+1;j++)
            bino[i][j]=factor[i]/factor[j]/factor[i-j];
    
    for(i=0;i<AC.n+1;i++){
        for(j=0;j<i;j++) {
            gama[i]=1.0;
            gama1[i]=0.0;
        };
        for(j=0;j<i;j++){
            gama[i]=gama[i]-gama[j]/(i-j+1.0);
            gama1[i]=gama1[i]-gama1[j]/(i-j+1.0);
        }
        //rabbish!!!
        /*
        if(i==0)
            gama1[i]=1.0;*/
        gama1[0]=1.0;
    }

    //beta for prediction (beta) and correction (beta1)
    s=1.0;
    for(i=0;i<AC.n;i++){
        AC.beta[i]=0.0;
        AC.beta1[i]=0.0;
        for(j=0;j<AC.n;j++){
            AC.beta[i]=AC.beta[i]+bino[j][i]*gama[j];
            AC.beta1[i]=AC.beta1[i]+bino[j][i]*gama1[j];
        };

        AC.beta[i]=s*AC.beta[i];
        AC.beta1[i]=s*AC.beta1[i];
        s=-s;
    };
    return;
}