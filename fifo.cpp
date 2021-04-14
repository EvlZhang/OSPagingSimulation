#include "fifo.h"
#include "page.h"
#include <queue>
#include <map>
using namespace std;
using namespace P;
void fifo(int k,int references[]){
    //making a queue of Pages
    queue<Pages> frameList;
    map<int,int> frameMap;
    for(int i=0;i<k;i++){
        Pages newPage(i,-1);
        frameList.push(newPage);
        frameMap.insert({i,-1});
    }
    int numFaults=0;
    int numMissed=0;
    int numHits=0;
    int len=frameList.size();
    //first reference is always a fault
    frameList.front().setRef(references[0]);
    frameMap.at(0)=references[0];
    numFaults++;
    frameList.push(frameList.front());
    frameList.pop();
    //start going through the page references
    for(int i=1;i<1000;i++){
        int ref=references[i];
        bool hit=false;
        for(int j=0;j<frameMap.size();j++){
            if(frameMap.at(j)==ref){
                hit=true;
                break;
            }
        }
        //cout<<"\n";
        if(hit==true){
            numHits++;
        }
        else if(frameList.front().getRef()==-1){
            frameList.front().setRef(ref);
            frameMap.at( frameList.front().getNum())=ref;
            frameList.push(frameList.front());
            frameList.pop();
            numMissed++;
        }
        else{
            //cout<<"Evicted front \n";
            frameList.front().setRef(ref);
            frameMap.at( frameList.front().getNum())=ref;
            frameList.push(frameList.front());
            frameList.pop();
            numFaults++;
        }
    }
    cout<<"Hits: "<<numHits<<"\n";
    cout<<"Misses: "<<numMissed<<"\n";
    cout<<"Faults: "<<numFaults<<"\n";
}