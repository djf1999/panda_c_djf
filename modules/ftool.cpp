#include"stdafx.h"

int index_( char* s1,char s2){
    char* str=strchr(s1,s2);
    int pos=(str-s1)+1;
    if (pos<0)pos=0;
    return pos;
}