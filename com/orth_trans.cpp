#include "orth_trans.h"
#include"dot.h"
#include "stdafx.h"

void orth_trans(bool& lsave_u,int &ntot,int& nobs,double**s,int ndim_x,int ndim_o,int ncol){
    //local variables
    int i,j,k,l;
    double sigma,alpha,beta,gama,u0;
    //
    //// u/v
    int nele,ipt[ndim_o],nrow;
    double    v[ndim_o];
    //# orthogonal triangle transformation for process parameters  
    //
    nrow=ntot+nobs;
    for(j=0;j<ntot;j++){              
        //  write(*,*) ' j ',j,lsave_u
        //
        ////take the non-zero elements
        nele=-1;
        for(i=j;i<nrow;i++){
            if((fabs(s[i][j])<1e-20)&&(i!=j)) continue; 
            nele=nele+1; 
            v[nele]=s[i][j]; 
            ipt[nele]=i;
        }
        //??sigma=dot_(nele-1,v,v);
        sigma=v[1]*v[1];
        if(sigma<=0.0) continue;    // all zero except the diag. element

        sigma=sqrt(sigma+v[0]*v[0]);
        if(v[0]>0.0) 
            sigma=-sigma;
            s[j][j]=sigma;
            v[0]=v[0]-sigma;
            beta=1.0/(sigma*v[0]);
        for(k=j+1;k<ntot+1;k++){
            alpha=0.0;
            for( i=0;i<nele;i++){
                alpha=alpha+s[ipt[i]][k]*v[i];
            }
            gama=alpha*beta ;
            if(gama<=1e-14) continue;
            for (i=0;i<nele;i++){
                s[ipt[i]][k]=s[ipt[i]][k]+gama*v[i];
            }
        }
        //
        //// save u and beta for quality control
        if(!lsave_u) continue;
        for(i=j;i<nrow+1;i++)
            s[i][j]=0.0;
        for (i=0;i<nele;i++){              
            s[ipt[i]+1][j]=v[i];
        }
        s[nrow+1][j]=beta;
    }

    return;
}

void sens_vector(int& npar,int& nobs,double**s,int& ndim_x,int& ndim_o,int& iobs,double*w){
    //// local variables 
    int j,k;
    double gama;
    memset(w,0,(npar+nobs)*sizeof(double));
    w[npar+iobs-1]=1.0;
    //
    for(j=0;j<npar;j++){
        gama=0.0;
        for(k=j;k<npar+nobs;k++)gama+=s[k+1][j]*w[k];

        gama*=s[npar+nobs+1][j];
        for(k=j;k<npar+nobs;k++) w[k]=w[k]+gama*s[k+1][j];
    }
    return;
}