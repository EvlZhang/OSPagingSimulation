#ifndef PAGE_H
#define PAGE_H
#include <iostream>
namespace P{
    class Pages{
        int frame_num;
        int reference; 
        //this is for sc
        int rFlag;
        int flagTimer;
    public:
        Pages(int num,int ref);
        Pages(int num,int ref,int flag, int flagTimer);
        Pages(int ref);
        int getNum();
        int getRef();
        void setNum(int num);
        void setRef(int ref);
        //below are for sc
        int getFlag();
        void setFlag(int flag);
        int getFlagTimer();
        void setFlagTimer(int timer);
    };
}

#endif