#include"polydf.h"

void polydf(double* x,double*y,int* l,int n,int ip,double*c,double*v,double& rms,int* ipt,double& dx,double& ft,int& ierr){
    //// local
    double xmin,xmax,ys,xnorm,xnorj,det,vmax,rms1;
    int i,j,k,m,neff,ik,ki,l_save[n];
    double    q[ip][ip],f[ip],a[ip];

    ierr=0;
    //  normalisation of independent argument

    xmin= 1e20;
    xmax=-1e20;

    //   searching the Max.  and  min.  argument values
    for (i=0;i<n;i++){
        l_save[i]=l[i];
        ipt[i]=0;
        if(l[i]<=1){ 
            if(x[i]>xmax) xmax=x[i];
            if(x[i]<xmin) xmin=x[i];
            v[i]=0.0;
        }
    }

    if(xmin==xmax) {
        ierr=1;
        return;
    }
    dx=(xmax+xmin)/2.0;
    ft=2.0/(xmax-xmin);

    //  initial importent parameter
    for(i=0;i<ip;i++){
        for(j=0;j<ip;j++)q[i][j]=0.0;
        f[i]=0.0;
    }

    neff=0;
    //  loop over all functional values
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    j=n;
    while(j>=2){      
        //   marked values
        if(l[j-1]==0){    

        //   searching next usable functional value to form difference
            m=j-1;
            while((m>=1)&&(l[m-1]>1)) {
                m=m-1;
            }
            if(m!=0){
                xnorj=(x[j-1]-dx)*ft;
                xnorm=(x[m-1]-dx)*ft;
                neff=neff+1;

            // computaion of a-matrix (row number j)
                for( k=0;k<ip;k++) a[k]=pow(xnorm,k)-pow(xnorj,k);
                

            // contribution to q-matrix (upper triangle)
                for(i=0;i<ip;i++)
                    for(k=i;k<ip;k++)
                        q[i][k]=q[i][k]+a[i]*a[k];

            // contribution to right hand side
                for( i=0;i<ip;i++) f[i]=f[i]+a[i]*(y[m]-y[j]);
            }
        }
        // next difference
        j=j-1;
    }

    if(neff<ip){
        printf("%s %s\n",neff,ip);
        ierr=2;
        return;
    }

    // lower triangle of q matrix
    for(i=0;i<ip;i++)
        for(k=0;k<i;k++)
            q[i][k]=q[k][i];
        
    

    // inversion of q matrix
    matinv((double**)q,ip,ip,det);
    if(fabs(det)<1e-20){
        ierr=3;
        return;
    }

    // solution vector (polynomial coefficients)
    for(i=0;i<ip;i++){
        c[i]=0.0;
        for(k=0;k<ip;k++)
            c[i]=c[i]+q[i][k]*f[k];
    };

    //  residuals, rms
    rms=0.0;
    vmax=0.0;
    j=n;
    while (j>=2) {
        if(l[j-1]<=1){
            m=j-1;
            while((m>=1)&&(l[m-1]>1)){
                m=m-1;
            }
            if(m!=0){
                    xnorj=(x[j-1]-dx)*ft;
                    xnorm=(x[m-1]-dx)*ft;
                    ys=0.0;
                    for(k=0;k<ip;k++) ys+=c[k]*(pow(xnorm,k)-pow(xnorj,k));
                    v[j-1]=ys-(y[m-1]-y[j-1]);
                    if(l[j-1]==0){
                        if((v[j-1])>vmax) vmax=v[j-1];
                        rms+=v[j-1]*v[j-1];
                    }
                    ipt[j-1]=m;
            //d     write(*,'(i6,f10.2)') j,v(j)
            }
        }
        j=j-1;
    }

    if(((neff-ip)!=0)&&(rms>0.0)){
        vmax=rms-vmax*vmax;
        rms=sqrt(rms/(neff-ip));
        if(((neff-ip-1)!=0)&&(vmax>0.0)){
            rms1=sqrt(vmax/(neff-ip-1));
            if((rms/rms1)>2.0) rms=rms1;
        }
    }
    else{
        printf(" BAD rms %f %d %d %d\n",rms,neff,ip,n);
        for(j=1;j<n;j++)
            printf("%6d %6d %6d %6d %6d %19.12f %19.12f\n", n,j,l[j],l_save[j],ipt[j],y[j],v[j]); 
        //  rms=0.d0
        ierr=4;
    }

    return;
}