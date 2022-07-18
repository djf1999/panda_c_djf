#include "matinv.h"

void matinv(double** a,int ndim,int n,double& d){
    int i,j,k,l[ndim],m[ndim];
    double  max_a,swap;

    d=1.0;
    for(k=0;k<n;k++){
        l[k]=k;
        m[k]=k;
        max_a=a[k][k];

        // find out the diag. element with max. abs. value.
        for(i=k;i<n;i++){
            for(j=k;j<n;j++){
                if((max_a-a[i][j])<0.0){ 
                    max_a=a[i][j];
                    m[k]=i;
                    l[k]=j;
                }
            } 
        }
        //
        //// rank defection or bad condition  
        if(max_a<1e-49){
            d=0.0;
            return;
        }
        //
        //// swap k and l(k) column      
        if(l[k]>k){   
            for(i=0;i<n;i++){
                swap=-a[i][k];
                a[i][k]=a[i][l[k]];
                a[i][l[k]]=swap;
            }
        }
        //
        //// swap k and m(k) raw
        if(m[k]>k){ 
            for(j=1;j<n;j++){
                swap=-a[k][j];
                a[k][j]=a[m[k]][j];
                a[m[k]][j]=swap;
            }
        }
        //
        //// elemination
        for(i=0;i<n;i++)
            if(i!=k) 
                a[k][i]=-a[k][i]/max_a;

        for (i=0;i<n;i++){
            for (j=0;j<n;j++){
                if((i!=k)&&(j!=k)) 
                    a[j][i]=a[j][i]+a[k][i]*a[j][k];
            }
        }
        //
        //// save invert part
        for (j=0;j<n;j++){
            if(j!=k) a[j][k]=a[j][k]/max_a;
        }
        a[k][k]=1/max_a;
    }
    //
    //// re-range raw and column as input
    for(k=n-1;k>=0;k--){
        if(l[k]>k){    
            for(j=1;j<n;j++){
                swap=a[k][j];
                a[k][j]=-a[l[k]][j];
                a[l[k]][j]=swap;
            }
        }            
        if(m[k]>k){
            for(i=0;i<n;i++){
                swap=a[i][k];
                a[i][k]=-a[i][m[k]];
                a[i][m[k]]=swap;
            }
        }
    }
    return;
}