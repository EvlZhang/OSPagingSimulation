#include "fifo.h"
#include "page.h"
#include <queue>
#include <deque>
#include <map>

using namespace std;
using namespace P;
map<int,int> lru(int k,int references[]){
    //using deque as a linked list
    //mostly the same as fifo except with deque methods
    deque<Pages> frameList;
    map<int,int> frameMap;
    map<int,int> totalRefs;
    for(int i=0;i<k;i++){
        Pages newPage(i,-1);
        frameList.push_back(newPage);
        frameMap.insert({i,-1});
    }
    for(int i=0;i<10;i++){
        totalRefs.insert({i,0});
    }
    int numEvicts=0;
    int numMissed=0;
    int numHits=0;
    int len=frameList.size();
    //first reference is always a fault
    frameList.front().setRef(references[0]);
    frameMap.at(0)=references[0];
    map<int,int>::iterator it=totalRefs.find(references[0]);
    it->second++;
    numMissed++;
    frameList.push_back(frameList.front());
    frameList.pop_front();
    //start going through the page references
    //again, mostly similar to fifo except with deque
    //and moving referenced pages to the end of the queue
    for(int i=1;i<1000;i++){
        int ref=references[i];
        bool hit=false;
        int frameNum=-1;
        map<int,int>::iterator it=totalRefs.find(references[i]);
        it->second++;
        for(int j=0;j<frameMap.size();j++){
            if(frameMap.at(j)==ref){
                hit=true;
                frameNum=j;
                break;
            }
        }
        //cout<<"\n";
        if(hit==true){
            //we have to find the used frame and move it to the bottom
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
            numMissed++;
            numEvicts++;
        }
    }
    cout<<"Hits: "<<numHits<<"\n";
    cout<<"Misses: "<<numMissed<<"\n";
    cout<<"Evicts: "<<numEvicts<<"\n";
    return totalRefs;
}