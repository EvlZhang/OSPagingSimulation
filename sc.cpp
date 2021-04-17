#include "sc.h"
#include "page.h"
#include <queue>
#include <deque>
#include <map>

using namespace std;
using namespace P;
map<int,int> sc(int k,int references[]){
    //sc uses the r bit, called Pages.rFlag here
    //frameList is deque for the at() method
    //frameList is NOT kept at order of recently used!
    deque<Pages> frameList;
    map<int,int> frameMap;
    map<int,int> totalRefs;
    //change this value if you want a different period for clearing r bits!!!!
    int defaultTimer=5;
    for(int i=0;i<k;i++){
        Pages newPage(i,-1,0,0);
        frameList.push_back(newPage);
        frameMap.insert({i,-1});
    }
    for(int i=0;i<10;i++){
        totalRefs.insert({i,0});
    }
    map<int,int>::iterator it=totalRefs.find(references[0]);
    it->second++;
    int numEvicts=0;
    int numMissed=0;
    int numHits=0;
    //first reference is always a fault
    frameList.front().setRef(references[0]);
    frameList.front().setFlag(1);
    frameList.front().setFlagTimer(defaultTimer);
    frameMap.at(0)=references[0];
    numMissed++;
    frameList.push_back(frameList.front());
    frameList.pop_front();

    //start going through the page references
    //the critical difference between this and fifo is that we have to go through the whole list 
    //to reduce rFlagTimer, so that we can periodicaly set rFlag back to 0
    for(int i=1;i<1000;i++){
        int ref=references[i];
        bool hit=false;
        int frameNum=-1;
        bool allFlagged=true;
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
            numHits++;
        }
        else if(frameList.front().getRef()==-1){
            frameList.front().setRef(ref);
            frameList.front().setFlag(1);
            frameList.front().setFlagTimer(defaultTimer);
            frameMap.at( frameList.front().getNum())=ref;
            frameList.push_back(frameList.front());
            frameList.pop_front();
            numMissed++;
        }
        else{

            // go through list to find one without rFlag
            int len=frameList.size();
            for(int j=0;j<len;j++){
                if(frameList.front().getFlag()==1){
                    frameList.front().setFlag(0);
                    frameList.push_back(frameList.front());
                    frameList.pop_front();
                }
                else{
                    allFlagged=false;
                    frameList.front().setRef(ref);
                    frameMap.at( frameList.front().getNum())=ref;
                    frameList.push_back(frameList.front());
                    frameList.pop_front();
                    break;
                }
            }
            //if everything is flagged before
            //the first one will not be flagged now because we put every flag as 0 above
            if(allFlagged==true){
                frameList.front().setRef(ref);
                frameMap.at( frameList.front().getNum())=ref;
                frameList.push_back(frameList.front());
                frameList.pop_front();
            }
                
            numMissed++;
            numEvicts++;
        }
        //go through the list to decrease rFlagTimer
        //while also setting the timer of the one just referenced to default
        for(int j=0;j<frameList.size();j++){
            if(frameList.at(j).getNum()==frameNum){
                if(hit==true){
                    frameList.at(j).setFlagTimer(defaultTimer);
                    frameList.at(j).setFlag(1);
                }
            }
            else if(frameList.at(j).getFlag()==1){
                frameList.at(j).setFlagTimer(frameList.at(j).getFlagTimer()-1);
                if(frameList.at(j).getFlagTimer()==0){
                    frameList.at(j).setFlag(0);
                }
            }
            else if(frameList.at(j).getFlag()==0){
                allFlagged=false;
            }
        }

    }
    cout<<"Hits: "<<numHits<<"\n";
    cout<<"Misses: "<<numMissed<<"\n";
    cout<<"Evicts: "<<numEvicts<<"\n";
    return totalRefs;
}