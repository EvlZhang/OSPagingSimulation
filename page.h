#ifndef PAGE_H
#define PAGE_H
#include <iostream>
namespace P{
    class Pages{
        int frame_num;
        int reference; 
    public:
        Pages(int num,int ref);
        Pages(int ref);
        int getNum();
        int getRef();
        void setNum(int num);
        void setRef(int ref);
    };
}

#endif