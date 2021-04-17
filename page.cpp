#include "page.h"
using namespace std;
using namespace P;

Pages::Pages(int num,int ref){
    frame_num=num;
    reference=ref;
}
Pages::Pages(int num,int ref,int flag,int timer){
    frame_num=num;
    reference=ref;
    rFlag=flag;
    flagTimer=timer;
}
Pages::Pages(int num){
    frame_num=num;
}
int Pages::getNum(){
    return frame_num;
}
int Pages::getRef(){
    return reference;
}
int Pages::getFlag(){
    return rFlag;
}
int Pages::getFlagTimer(){
    return flagTimer;
}
void Pages::setNum(int num){
    frame_num=num;
}
void Pages::setRef(int ref){
    reference=ref;
}
void Pages::setFlag(int flag){
    rFlag=flag;
}
void Pages::setFlagTimer(int timer){
    flagTimer=timer;
}