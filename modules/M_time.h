#ifndef _M_TIME_H_
#define _M_TIME_H_
struct T_time{
    char ctype[10];
    int  jd;
    double sod;
    T_time(){
        memset(ctype,0,10);
        jd=0;
        sod=0.0;
        strcpy(ctype,"GPST");
    }
};

void timeinc(T_time& T0,double dt,T_time&T1);

double  timedif(T_time&T0,T_time&T1);
double  time2fjd(T_time&T);
double  fjd2time(double fjd,T_time&T);
bool  l_check_intv(int nintv,T_time&TB,T_time&TE,double extend,T_time&TEPO1,T_time&TEPO2,int i);

#endif