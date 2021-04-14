#include <iostream>
#include <random>
using namespace std;
int main(){
    //read input number k
    int k;
    cout<<"Enter the number(k) of frames: \n";
    cin>>k;
    int alg;
    cout<<"Enter the replacement algorithm \n";
    cout<<"0 for FIFO, 1 for LRU, 2 for Second Chance: \n";
    cin>>alg;
    //seeds and engine
    default_random_engine generator;
    uniform_int_distribution<long int> distribution(0,0x7FFFFFFF);
    //generate and perform reduction according to rules
    int references[1000];
    for(int i=0;i<1000;i++){
        int geNum=distribution(generator)%100;
        for(int j=0;pow(j,2)<=geNum;j++){
            if(pow(j,2)<=geNum&&geNum<pow((j+1),2)){
                references[i]=j;
            }
        }
    }

    return 0;
}
