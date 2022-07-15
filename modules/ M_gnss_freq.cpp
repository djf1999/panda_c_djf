#include"M_gnss_freq.h"

void set_sat_freq_basic(){
    if(nsys_in_freq==0){ 
    nsys_in_freq=7;

    SYSFREQ[0].nfreq=3;
    SYSFREQ[0].FREQ[0].csysid[0]='G';SYSFREQ[0].FREQ[0].cfreq_band[0]='L1';SYSFREQ[0].FREQ[0].cfreq_id='1';
    SYSFREQ[0].FREQ[0].freq=1575.420e6;SYSFREQ[0].FREQ[0].wlength=0.0;

    SYSFREQ[0].FREQ[1].csysid[0]='G';SYSFREQ[0].FREQ[1].cfreq_band[0]='L2';SYSFREQ[0].FREQ[1].cfreq_id='2';
    SYSFREQ[0].FREQ[1].freq=1227.600e6;SYSFREQ[0].FREQ[1].wlength=0.0;

    SYSFREQ[0].FREQ[2]=T_trans_freq('G','L5','5',1176.450d6,0.d0)
    SYSFREQ[0].FREQ[3]=T_trans_freq(' ','  ',' ',      0.d0,0.d0)
    SYSFREQ[0].FREQ[4]=T_trans_freq(' ','  ',' ',      0.d0,0.d0)
    SYSFREQ[0].FREQ[5]=T_trans_freq(' ','  ',' ',      0.d0,0.d0)

    SYSFREQ[1].nfreq=6 
    SYSFREQ[1].FREQ[0]=T_trans_freq('C','L2' ,'2',1561.098D6,0.d0)!B1I
    SYSFREQ[1].FREQ[1]=T_trans_freq('C','L6' ,'6',1268.520D6,0.d0)!B3I
    SYSFREQ[1].FREQ[2]=T_trans_freq('C','L7' ,'7',1207.140D6,0.d0)
//   SYSFREQ[1].FREQ[1]=T_trans_freq('C','L7' ,'7',1207.140d6,0.d0)
//   SYSFREQ[1].FREQ[2]=T_trans_freq('C','L3' ,'3',1268.520d6,0.d0)
    SYSFREQ[1].FREQ[3]=T_trans_freq('C','L1' ,'1',1561.098D6,0.d0)
    SYSFREQ[1].FREQ[4]=T_trans_freq('C','L3' ,'3',1268.520D6,0.d0)
    SYSFREQ[1].FREQ[5]=T_trans_freq('C','L8' ,'8',1197.795D6,0.d0)

    SYSFREQ[2].nfreq=6
    SYSFREQ[2].FREQ[0]=T_trans_freq('E','E1' ,'1',1575.420d6,0.d0)
    SYSFREQ[2].FREQ[3]=T_trans_freq('E','E6' ,'6',1278.750d6,0.d0)
    SYSFREQ[2].FREQ[4]=T_trans_freq('E','E5' ,'8',1191.795d6,0.d0)
    SYSFREQ[2].FREQ[1]=T_trans_freq('E','E5a','5',1176.450d6,0.d0)
    SYSFREQ[2].FREQ[2]=T_trans_freq('E','E5b','7',1207.140d6,0.d0)
    SYSFREQ[2].FREQ[5]=T_trans_freq('E','E6a','3',1207.140d6,0.d0)

    SYSFREQ[3].nfreq=5
    SYSFREQ[3].FREQ[0]=T_trans_freq('R','L1' ,'1',1602.000d6,0.5625d6)
    SYSFREQ[3].FREQ[1]=T_trans_freq('R','L2' ,'2',1246.000d6,0.4375d6)
    SYSFREQ[3].FREQ[2]=T_trans_freq('R','L5' ,'5',1204.704d6,    0.d0)
    SYSFREQ[3].FREQ[3]=T_trans_freq('R','L7' ,'7',1204.704d6,    0.d0)
    SYSFREQ[3].FREQ[4]=T_trans_freq('R','L3' ,'3',1204.704d6,    0.d0)
    SYSFREQ[3].FREQ[5]=T_trans_freq(' ','  ' ,' ',      0.d0,0.d0)

    SYSFREQ[4].nfreq=2
    SYSFREQ[4].FREQ[0]=T_trans_freq('S','L1','1',1575.420d6,0.d0)
    SYSFREQ[4].FREQ[1]=T_trans_freq('S','L5','5',1176.450d6,0.d0)
    SYSFREQ[4].FREQ[2]=T_trans_freq(' ','  ',' ',      0.d0,0.d0)
    SYSFREQ[4].FREQ[3]=T_trans_freq(' ','  ',' ',      0.d0,0.d0)
    SYSFREQ[4].FREQ[4]=T_trans_freq(' ','  ',' ',      0.d0,0.d0)
    SYSFREQ[4].FREQ[5]=T_trans_freq(' ','  ' ,' ',     0.d0,0.d0)

    SYSFREQ[5].nfreq=4
    SYSFREQ[5].FREQ[0]=T_trans_freq('J','L1','1',1575.420d6,0.d0)
    SYSFREQ[5].FREQ[1]=T_trans_freq('J','L2','2',1227.600d6,0.d0)
    SYSFREQ[5].FREQ[2]=T_trans_freq('J','L5','5',1176.450d6,0.d0)
    SYSFREQ[5].FREQ[3]=T_trans_freq('J','L6','6',1269.640d6,0.d0)   ! use E E6
    SYSFREQ[5].FREQ[4]=T_trans_freq(' ','  ',' ',      0.d0,0.d0)
    SYSFREQ[5].FREQ[5]=T_trans_freq(' ','  ' ,' ',      0.d0,0.d0)

    SYSFREQ[6].nfreq=2
    SYSFREQ[6].FREQ[0]=T_trans_freq('I','L5','5',1176.450d6,0.d0)
    SYSFREQ[6].FREQ[1]=T_trans_freq('I','L9','9',2492.028d6,0.d0)
    SYSFREQ[6].FREQ[2]=T_trans_freq('I','  ',' ',      0.d0,0.d0)
    SYSFREQ[6].FREQ[3]=T_trans_freq('I','  ',' ',      0.d0,0.d0)
    SYSFREQ[6].FREQ[4]=T_trans_freq('I','  ',' ',      0.d0,0.d0)
    SYSFREQ[6].FREQ[5]=T_trans_freq('I','  ',' ',      0.d0,0.d0)

}

return;
}