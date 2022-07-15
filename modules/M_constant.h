#ifndef _M_CONSTANT_H_
#define _M_CONSTANT_H_
#include "M_dimpar.h"

const double pi =3.14159265358979311599796346854419;
const double twopi = 2*3.14159265358979311599796346854419;
const double rad2deg=180.0/pi;
const double rad2sec=rad2deg*3600.0;
const double rad2tsec=rad2sec/15.0;  
const double gme=3.9860044180;                 // m**3/s**2
const double wearth=7.2921151467e-5;             // angular velocity of the earth
const double vlight=299792458.0;
//
// tdt = gps + toffset_gps2tdt
const double toffset_tai2tdt =32.184/86400.0;
const double toffset_gps2tdt =(32.184 + 19.0)/86400.0;

struct T_datum{
    char code[8];
    double semi; 
    double finv; 
    double shift[3];
    T_datum ()
    {
        strcpy(code,"WGS84");
        semi=6378137;
        finv=298.257223563;
        shift[0]=0.0;shift[1]=0.0;shift[2]=0.0;
    };
};
T_datum GD;

#endif