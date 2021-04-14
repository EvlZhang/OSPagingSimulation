#include "page.h"
using namespace std;
using namespace P;

Pages::Pages(int num,int ref){
    frame_num=num;
    reference=ref;
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
void Pages::setNum(int num){
    frame_num=num;
}
void Pages::setRef(int ref){
    reference=ref;
}