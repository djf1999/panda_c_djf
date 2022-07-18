#include "addneq.h"
#include "dot.h"


void addneq(int& nd,int& np,int& ic,double* w,double* a,double* b,double* an,double*bn,double ltpl)  {
    int ip,i,j,k,l,iw,ia,ik;
    double h[nd];
    //
    //// functions called
    double dot;

    for(ip=0;ip<np;ip++){
        // calculation of  a * P => h
        if(ic==0){
            for (i=0;i<nd;i++)
                h[i]=a[np*i+ip];
        }
        else{
            for(i=0;i<nd;i++){
                h[i]=0.0;
                for(l=0;l<nd;l++){
                    ia=ip+l*np;
                    iw=l+i*nd;
                    h[i]=h[i]+a[ia]*w[iw];
                }
        };
        //  calculation of a * P ( = h ) * b => bn  a * P ( = h ) * a => an
        for(i=0;i<nd;i++){
                bn[ip]=bn[ip]+h[i]*b[i];
                for( k=0;k<np;k++){
                ik=ip+k*np;
                ia=k+(i-1)*np;
                an[ik]=an[ik]+h[i]*a[ia];
            }
        }
        //  next equation
    }

    // calculation  b * P * b

    if(ic==0) {
        for(i=0;i<nd;i++){
            h[i]=0.0;
            for(k=0;k<nd;k++){
                iw=i+k*nd;
                h[i]=h[i]+w[iw]*b[k];
            }
        }
        ltpl=ltpl+dot_(nd,h,b);
    }
    else
        ltpl=ltpl+dot_(nd,b,b);
    }
    return;
}