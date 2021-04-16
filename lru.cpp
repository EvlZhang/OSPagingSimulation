#include "fifo.h"
#include "page.h"
#include <queue>
#include <deque>
#include <map>

using namespace std;
using namespace P;
void lru(int k,int references[]){
    //using deque as a linked list
    //mostly the same as fifo except with deque methods
    deque<Pages> frameList;
    map<int,int> frameMap;
    for(int i=0;i<k;i++){
        Pages newPage(i,-1);
        frameList.push_back(newPage);
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
    frameList.push_back(frameList.front());
    frameList.pop_front();
    //start going through the page references
    //again, mostly similar to fifo except with deque
    //and moving referenced pages to the end of the queue
    for(int i=1;i<1000;i++){
        int ref=references[i];
        bool hit=false;
        int frameNum=-1;
        for(int j=0;j<frameMap.size();j++){
            if(frameMap.at(j)==ref){
                hit=true;
                frameNum=j;
                break;
            }
        }
        //cout<<"\n";
        if(hit==true){
            for(int j=0;j<frameList.size();j++){
                if(frameList.at(j).getNum()==frameNum){
                    frameList.push_back(frameList.at(j));
                    frameList.erase(frameList.begin()+j);
                    break;
                }
            }
            numHits++;
        }
        else if(frameList.front().getRef()==-1){
            frameList.front().setRef(ref);
            frameMap.at( frameList.front().getNum())=ref;
            frameList.push_back(frameList.front());
            frameList.pop_front();
            numMissed++;
        }
        else{
            //cout<<"Evicted front \n";
            frameList.front().setRef(ref);
            frameMap.at( frameList.front().getNum())=ref;
            frameList.push_back(frameList.front());
            frameList.pop_front();
            numFaults++;
        }
    }
    cout<<"Hits: "<<numHits<<"\n";
    cout<<"Misses: "<<numMissed<<"\n";
    cout<<"Faults: "<<numFaults<<"\n";
}