#include "stdafx.h"
#include "get_fraction.h"

double get_fraction(double x,double ymin){
    double y=0.0;
    y=x-int(x+0.5);
    
    if(fabs(ymin)<1e-20){
        if(y<0.0)
            y+=1.0;
        else if(y>=1.0)
            y=y-1.0;
    }
    else if(fabs(ymin+0.5)<1e-20){
        if(y<-0.5)
            y+=1.0;
        else if(y>=0.5)
            y-=1.0;
    }
    else{
        if(y>=1.0)
            y-=1.0;
    }
    return y;
}

