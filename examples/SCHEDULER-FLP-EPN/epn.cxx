/**
 * epn.cxx
 *
 */

#include "epn.h"
#include "FairMQPoller.h"
#include "Message.h"
#include <iostream>
#include <string>
#include <random>
#include <thread>



using namespace std;

namespace example_SCHEDULER_FLP_EPN
{

epn::epn()
    : Id(0)
    , freeSlots(0)
    , maxSlots(4)
    , numEPNS(0)
    , numFLPS(0)
    , procTime(10)
    , procDev(3)
    ,channelname()
    ,channel("data")
    ,rcvdSTFs()
    ,sTF(1)
    {
    static_assert(std::is_pod<EPNtoScheduler>::value==true, "my struct  is not pod");
    }

void epn::InitTask()
{
        Id = fConfig->GetValue<int>("myId");
        maxSlots = 4;
        freeSlots = maxSlots;
        numEPNS = fConfig->GetValue<uint64_t>("numEPNS");
        numFLPS = fConfig->GetValue<uint64_t>("numFLPS");
        channelname=fConfig->GetValue<char>("channelname");
        std::thread th1 = senderThread(&freeSlots, &numEPNS, &Id);
        th1.detach();
    }


bool epn::ConditionalRun()
{

     receive();


return true;



}

std::string epn::getChannel(char number){
   std::string s;
   s.push_back(number);
   std::string res = channel+s;
   return res;
   }


void epn::receive(){   
// TODO: poller

for(uint64_t i=0; i<numFLPS; i++){
    auto &myRecvChan = GetChannel("data", i);

    FLPtoEPN messagei;
    FairMQMessagePtr aMessage = myRecvChan.NewMessage();

    myRecvChan.Receive(aMessage);

    std::memcpy(&messagei, aMessage->GetData(), sizeof(FLPtoEPN));

    // you can assume the message is valid
    // MAKE SURE to fill the correct `IdOfTF` at the FLP side!
    LOG(INFO) << "Epn received TF: " << messagei.IdOfTF << " from EPN: " <<messagei.IdOfFlp;

    // rewrite this as we discussed
    rcvdSTFs[messagei.IdOfTF] += 1;

    // assert the boundaries
    assert(rcvdSTFs[messagei.IdOfTF] <= numFLPS);
    // check if all FLPs sent the same STF (TF is complete)
    if (rcvdSTFs[messagei.IdOfTF] == numFLPS) {
        float x = getDelay();
        LOG(INFO) << "Delay work for:" << x << "seconds\n" << endl;
        std::thread t3(MyDelayedFun, x, &freeSlots);
        t3.detach();
    }
  }
}


bool epn::checkFLP(){
  bool result;
  for(int i=1;i <= numFLPS;i++){
    result=(rcvdSTFs.count(i)>0);
    if(!result){
      return result;
    }
  }
  return result;
}

void epn::rcvdSTFsToFile(){
  ofstream myfile;
  myfile.open("FLPdata.txt", std::ios_base::app);
  for(auto a = rcvdSTFs.begin(); a != history.end(); a ++ ){
      //myfile << (*a).first << " ";
      for(uint64_t i = 0; i < (numEPNS-1); i++){
          myfile << history[(*a).first].at(i).memVal << ", ";

      }
      myfile << history[(*a).first].at(numEPNS-1).memVal << endl;
  }
  }

void epn::send(uint64_t* memory, uint64_t* numepns, int* id){
        while(true){
            auto &mySendingChan = GetChannel("epnsched");
            EPNtoScheduler myMsg;
            myMsg.Id = *id;
            myMsg.freeSlots = *memory;
            myMsg.numEPNs = *numepns;
            FairMQMessagePtr message = mySendingChan.NewMessage(sizeof(EPNtoScheduler));
            std::memcpy(message->GetData(), &myMsg, sizeof(EPNtoScheduler));
            mySendingChan.Send(message);

            LOG(INFO)<<"sent ID: "<<myMsg.Id<<" and amount of free slots              "<<myMsg.freeSlots<< " general amount of EPNs: "  <<myMsg.numEPNs << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(long  (1000)));
            }
}

thread epn::senderThread(uint64_t* memory, uint64_t* numepns, int* id) {
          return std::thread([=] {
          this->send(memory,numepns,id);
          });
      }

void epn:: MyDelayedFun(float delayWork, uint64_t* memory){
     (*memory)--;
     cout<<"amount of memory slots after decrementing: "<<*memory<<endl;
     std::this_thread::sleep_for(std::chrono::milliseconds(long  (delayWork*1000)));
     cout<<"Delayed thread executioning the work now! \n";
     (*memory)++;
     cout<<"amount of memory slots after incrementing: "<<*memory<<endl;
}

float epn:: getDelay(){
     std::default_random_engine generator;
     std::normal_distribution<float> distribution(procTime, procDev);
     float delay = distribution(generator);
     cout<<"Delay work for:" << delay <<"seconds\n";
     return delay;
}







epn::~epn()
{
}

}
