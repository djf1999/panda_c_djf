#include"M_gnss_freq.h"

void set_sat_freq_basic(){
    if(nsys_in_freq==0){ 
    
        nsys_in_freq=7;

        SYSFREQ[0].nfreq=3;
        SYSFREQ[0].FREQ[0]=T_trans_freq('G',"L1",'1',1575.420e6,0.0);
        SYSFREQ[0].FREQ[1]=T_trans_freq('G',"L2",'2',1227.600e6,0.0); 
        SYSFREQ[0].FREQ[2]=T_trans_freq('G',"L5",'5',1176.450e6,0.0);
        SYSFREQ[0].FREQ[3]=T_trans_freq(' ',"  ",' ',      0.0,0.0);
        SYSFREQ[0].FREQ[4]=T_trans_freq(' ',"  ",' ',      0.0,0.0);
        SYSFREQ[0].FREQ[5]=T_trans_freq(' ',"  ",' ',      0.0,0.0);

        SYSFREQ[1].nfreq=6 ;
        SYSFREQ[1].FREQ[0]=T_trans_freq('C',"L2" ,'2',1561.098e6,0.0);//B1I
        SYSFREQ[1].FREQ[1]=T_trans_freq('C',"L6" ,'6',1268.520e6,0.0);//B3I
        SYSFREQ[1].FREQ[2]=T_trans_freq('C',"L7" ,'7',1207.140e6,0.0);
    //   SYSFREQ[1].FREQ[1]=T_trans_freq('C',"L7" ,'7',1207.140e6,0.0);
    //   SYSFREQ[1].FREQ[2]=T_trans_freq('C',"L3" ,'3',1268.520e6,0.0);
        SYSFREQ[1].FREQ[3]=T_trans_freq('C',"L1",'1',1561.098e6,0.0);
        SYSFREQ[1].FREQ[4]=T_trans_freq('C',"L3" ,'3',1268.520e6,0.0);
        SYSFREQ[1].FREQ[5]=T_trans_freq('C',"L8",'8',1197.795e6,0.0);

        SYSFREQ[2].nfreq=6;
        SYSFREQ[2].FREQ[0]=T_trans_freq('E',"E1" ,'1',1575.420e6,0.0);
        SYSFREQ[2].FREQ[3]=T_trans_freq('E',"E6" ,'6',1278.750e6,0.0);
        SYSFREQ[2].FREQ[4]=T_trans_freq('E',"E5" ,'8',1191.795e6,0.0);
        SYSFREQ[2].FREQ[1]=T_trans_freq('E',"E5a",'5',1176.450e6,0.0);
        SYSFREQ[2].FREQ[2]=T_trans_freq('E',"E5b",'7',1207.140e6,0.0);
        SYSFREQ[2].FREQ[5]=T_trans_freq('E',"E6a",'3',1207.140e6,0.0);

        SYSFREQ[3].nfreq=5;
        SYSFREQ[3].FREQ[0]=T_trans_freq('R',"L1" ,'1',1602.000e6,0.5625e6);
        SYSFREQ[3].FREQ[1]=T_trans_freq('R',"L2" ,'2',1246.000e6,0.4375e6);
        SYSFREQ[3].FREQ[2]=T_trans_freq('R',"L5" ,'5',1204.704e6,    0.0);
        SYSFREQ[3].FREQ[3]=T_trans_freq('R',"L7" ,'7',1204.704e6,    0.0);
        SYSFREQ[3].FREQ[4]=T_trans_freq('R',"L3" ,'3',1204.704e6,    0.0);
        SYSFREQ[3].FREQ[5]=T_trans_freq(' ',"  " ,' ',      0.0,0.0);

        SYSFREQ[4].nfreq=2;
        SYSFREQ[4].FREQ[0]=T_trans_freq('S',"L1",'1',1575.420e6,0.0);
        SYSFREQ[4].FREQ[1]=T_trans_freq('S',"L5",'5',1176.450e6,0.0);
        SYSFREQ[4].FREQ[2]=T_trans_freq(' ',"  ",' ',      0.0,0.0);
        SYSFREQ[4].FREQ[3]=T_trans_freq(' ',"  ",' ',      0.0,0.0);
        SYSFREQ[4].FREQ[4]=T_trans_freq(' ',"  ",' ',      0.0,0.0);
        SYSFREQ[4].FREQ[5]=T_trans_freq(' ',"  " ,' ',     0.0,0.0);

        SYSFREQ[5].nfreq=4;
        SYSFREQ[5].FREQ[0]=T_trans_freq('J',"L1",'1',1575.420e6,0.0);
        SYSFREQ[5].FREQ[1]=T_trans_freq('J',"L2",'2',1227.600e6,0.0);
        SYSFREQ[5].FREQ[2]=T_trans_freq('J',"L5",'5',1176.450e6,0.0);
        SYSFREQ[5].FREQ[3]=T_trans_freq('J',"L6",'6',1269.640e6,0.0);   //use E E6
        SYSFREQ[5].FREQ[4]=T_trans_freq(' ',"  ",' ',      0.0,0.0);
        SYSFREQ[5].FREQ[5]=T_trans_freq(' ',"  " ,' ',      0.0,0.0);

        SYSFREQ[6].nfreq=2;
        SYSFREQ[6].FREQ[0]=T_trans_freq('I',"L5",'5',1176.450e6,0.0);
        SYSFREQ[6].FREQ[1]=T_trans_freq('I',"L9",'9',2492.028e6,0.0);
        SYSFREQ[6].FREQ[2]=T_trans_freq('I',"  ",' ',      0.0,0.0);
        SYSFREQ[6].FREQ[3]=T_trans_freq('I',"  ",' ',      0.0,0.0);
        SYSFREQ[6].FREQ[4]=T_trans_freq('I',"  ",' ',      0.0,0.0);
        SYSFREQ[6].FREQ[5]=T_trans_freq('I',"  ",' ',      0.0,0.0);

    };

    return;
}