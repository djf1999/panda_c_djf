#include"polyno.h"

void polyno(int& nsampl,int& ndegre,double* argu,double* funct,int* iflag,int& j0,double* weight,\
    int& ires,double* v,double&rms,double*para,double&dx,double&ft,int& ierr){

    double anor[ndegre*2][ndegre*2],w[ndegre*2],a[ndegre*2],xmin,xmax,ys,det,xnorm;
    int i,j,k,ik,ki,nused,nequ;
    bool bias;

    ierr=0;

    bias=false;
    nequ=ndegre;
    if(j0!=0) {
        bias=true;
        nequ=nequ+1;
    }

    //  normalisation of variabl
    xmin= 1e32;
    xmax=-1e32;
    for(i=0;i<nsampl;i++){
        if(iflag[i]<2) {
            if(argu[i]>xmax) xmax=argu[i];
            if(argu[i]<xmin) xmin=argu[i];
        }
    }
    if((xmax-xmin)<=0) {
        ierr=1;
        return;
    }
    dx=(xmax+xmin)/2.0;
    ft=2.0/(xmax-xmin);
    //
    // initialization of normal equation
    for(i=0;i<nequ;i++){
        w[i]=0.0;
        for(j=0;j<nequ;j++)
            anor[i][j]=0.0;
    }
    //
    //// obs. equation coefficience
    a[0]=1.0;
    //
    //// loop over all samples
    nused=0;

    for(j=0;j<nsampl;j++){
        //
        //// if sample is marked ( igflag != 0 )
        if(iflag[j]==0) {    
            nused=nused+1;

            //  a-matrix
            xnorm=(argu[j]-dx)*ft;
            for(k=1;k<nequ;k++) a[k]=pow(xnorm,(k-1));
            if(bias) {
                a[nequ]=0.0;
                if(j>=j0) a[nequ]=1.0;
            }
            
            //  contribution to normal-matrix ANOR  (lower triangle)
            for(i=1;i<nequ;i++)
            for (k=i;k<nequ;k++) anor[i][k]=anor[i][k]+a[i]*a[k]*weight[j];

            //  contribution to right hand side
            for(i=0;i<nequ;i++)w[i]+=a[i]*funct[j]*weight[j];
        }

        //  next sample
    }
    if(nused<nequ){ 
        ierr=2;
        return;
    }

    //  lower triangle of normal matrix
    for (i=0;i<nequ;i++)   
        for(k=0;k<i;k++)
            anor[i][k]=anor[k][i];

    //  inversion of normal matrix
    matinv((double**)anor,ndegre*2,nequ,det);
    if(det==0.0){
        ierr=3;
        return;
    }

    //  solution vector (polynomial coefficients)
    for(i=0;i<nequ;i++){   
        para[i]=0.0;
        for(k=0;k<nequ;k++){  
            para[i]=para[i]+anor[i][k]*w[k];
        }
    }

    //  compute residuals and rms
    if(ires!=0){    
        rms=0.0;
        for(j=0;j<nsampl;j++){
            if(iflag[j]<2){
                a[0]=1.0;
                xnorm=(argu[j]-dx)*ft;
                for(k=1;k<nequ;k++)  a[k]=pow(xnorm,(k-1));
                if(bias){
                    a[nequ]=0.0;
                    if(j>=j0) a[nequ]=1.0;
                }
                ys=0.0;  
                for( k=0;k<nequ;k++) ys+=para[k]*a[k];
                v[j]=ys-funct[j];
                // write(*,'(2i6,3f16.2)') j,iflag(j),v(j),funct(j),ys
                if(iflag[j]==0) rms+=v[j]*v[j];
            }
        }
    }

    if(((nused-nequ)!=0)&&(rms>0.0)) 
        rms=sqrt(rms/(1.0*(nused-nequ)));
    else
        rms=0.0;
    
    if(bias) {
        para[nequ+1-1]=rms*sqrt(anor[nequ-1][nequ-1]);
    }
    return;
}