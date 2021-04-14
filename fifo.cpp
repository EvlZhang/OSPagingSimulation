#include "fifo.h"
#include "page.h"
#include <queue>
using namespace std;
using namespace P;
void fifo(int k,int references[]){
    //making a queue of Pages
    queue<Pages> frameList;
    for(int i=0;i<k;i++){
        Pages newPage(i,-1);
        frameList.push(newPage);
    }

    int numFaults=0;
    int numMissed=0;
    int numHits=0;
    int len=frameList.size();
    //first reference is always a fault
    frameList.front().setRef(references[1]);
    numFaults++;
    frameList.push(frameList.front());
    frameList.pop();

    //start going through the page references
    for(int i=1;i<1000;i++){
        int ref=references[i];

        if(frameList.back().getRef()==ref){
            numHits++;
        }
        else if(frameList.front().getRef()==-1){
            frameList.front().setRef(references[i]);
            frameList.push(frameList.front());
            frameList.pop();
            numMissed++;
        }
        else{
            //cout<<"Evicted front \n";
            frameList.front().setRef(references[i]);
            frameList.push(frameList.front());
            frameList.pop();
            numFaults++;
        }

    }
    cout<<"Hits: "<<numHits<<"\n";
    cout<<"Misses: "<<numMissed<<"\n";
    cout<<"Faults: "<<numFaults<<"\n";
    // for(int i=0;i<len;i++){
    //     cout<<frameList.front().getRef();
    //     frameList.pop();
    // }
}