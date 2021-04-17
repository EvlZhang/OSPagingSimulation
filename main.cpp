//Evelyn Zhang 
#include <iostream>
#include <random>
#include <map>
#include "fifo.h"
#include "lru.h"
#include "sc.h"
#include <ctime>
using namespace std;
int main(){
    //read input number k
    int k;
    cout<<"Enter the number(k) of frames: \n";
    cin>>k;
    int alg;
    cout<<"Enter the replacement algorithm ";
    cout<<"0 for FIFO, 1 for LRU, 2 for Second Chance, 3 for ALL: \n";
    //cout<<"If you want to run all algorithms, enter 4 \n";
    cin>>alg;
    //engine using seed with time(0)
    unsigned seed=time(0);
    default_random_engine generator;
    generator.seed(seed);
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
    map<int,int> totalRefs;
    if(alg==0){
        cout<<"Number of frames: "<<k<<"\n";
        cout<<"Using Method FIFO \n";
        totalRefs=fifo(k,references);
        cout<<"\n";
        cout<<"Total references: \n";
    }
    else if(alg==1){
        cout<<"Number of frames: " <<k<<"\n";
        cout<<"Using Method LRU \n";
        totalRefs=lru(k,references);
        cout<<"\n";
        cout<<"Total references: \n";
    }
    else if(alg==2){
        cout<<"Number of frames: " <<k<<"\n";
        cout<<"Using Method Second Chance \n";
        totalRefs=sc(k,references);
        cout<<"\n";
        cout<<"Total references: \n";
    }
    else if(alg==3){
        //totalRefs will be the same anyway
        cout<<"Number of frames: "<<k<<"\n";
        cout<<"Using Method: FIFO \n";
        totalRefs=fifo(k,references);
        cout<<"\n";
        cout<<"Number of frames: "<<k<<"\n";
        cout<<"Using Method: LRU \n";
        totalRefs=lru(k,references);
        cout<<"\n";
        cout<<"Number of frames: "<<k<<"\n";
        cout<<"Using Method: Second Chance \n";
        totalRefs=sc(k,references);
        cout<<"\n";
        cout<<"Total references are the same all algorithms: \n";
    }
    else{
        cout<<"Invalid replacement algorithm, terminated!!!";
        return 1;
    }

    for(int i=0;i<totalRefs.size();i++){
        map<int,int>::iterator it=totalRefs.find(i);
        cout<<"Page "<<i<<" referenced "<<it->second<<" times\n";
    }

    return 0;
}
