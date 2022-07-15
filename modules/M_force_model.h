#ifndef _M_FORCE_MODEL_H_
#define _M_FORCE_MODEL_H_

#include"M_dimpar.h"

  const int max_force_model=12;
  const int max_force_param=55;
//
//// parameter name
   const char  param_all[max_force_param][len_parname]={
         "Kd_BERN   ","Ky_BERN   ","Kb_BERN   ","Kdc1_BERN ","Kds1_BERN "    
        ,"Kyc1_BERN ","Kys1_BERN ","Kbc1_BERN ","Kbs1_BERN ","Kdc2_ECOM "    
        ,"Kds2_ECOM ","Kdc4_ECOM ","Kds4_ECOM ","Kbc1_ECOM ","Kbs1_ECOM "    
        ,"SR_scale  ","DRAG_c    ","AERA_x    ","AREA_y    ","AREA_z    "    
        ,"EMP_Ac    ","EMP_Bc    ","EMP_Sc1   ","EMP_Cc1   ","EMP_Sc2   "    
        ,"EMP_Cc2   ","EMP_Aa    ","EMP_Ba    ","EMP_Sa1   ","EMP_Ca1   "    
        ,"EMP_Sa2   ","EMP_Ca2   ","EMP_Ar    ","EMP_Br    ","EMP_Sr1   "    
        ,"EMP_Cr1   ","EMP_Sr2   ","EMP_Cr2   ","          ","          "    
        ,"GMe       ","GMs       ","GMm       ","          ","          "    
        ,"ACC_Bx    ","ACC_By    ","ACC_Bz    ","ACC_Kx    ","ACC_Ky    "    
        ,"ACC_Kz    ","VABreak   ","VCBreak   ","VRBreak   ","          "};
//
//// force model name
   const char force_all[max_force_model][len_parname]={     
         "Solid earth tide     ","Ocean tide           ","Gravity model        "  
        ,"Point mass           ","Solar radiation      ","Atmosphere drag      "  
        ,"Relativity           ","Earth radiation      ","Customer model       "  
        ,"Accelerometer obs.   ","                     ","                     "};

//
//// initial position & velocity 
   const char cposvel[6][len_parname]={"PXSAT","PYSAT","PZSAT","VXSAT","VYSAT","VZSAT"};
//
  struct T_FORCE_MODEL{
    char force_name[len_parname];
    char force_model[256];
    T_FORCE_MODEL(){
        memset(force_name,0,len_parname);
        memset(force_model,0,256);
    };
  };

bool l_orbit_parameter(char* cparname,int& length);

#endif