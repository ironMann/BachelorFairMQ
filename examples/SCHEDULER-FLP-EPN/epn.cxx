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
    , numEPNS(0)
    , procTime(10)
    , procDev(3)
    , maxSlots(4)
    ,amountFlps(0)
    ,channelname()
    ,channel("data")
    {
    static_assert(std::is_pod<EPNtoScheduler>::value==true, "my struct  is not pod");
    }

void epn::InitTask()
{
        Id = fConfig->GetValue<int>("myId");
        maxSlots = 4;
        freeSlots = maxSlots;
        numEPNS = fConfig->GetValue<uint64_t>("numEPNS");
        channelname=fConfig->GetValue<char>("channelname");
        std::thread th1 = senderThread(&freeSlots, &channelname, &numEPNS, &Id);
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
        auto &myRecvChan = GetChannel(getChannel(channelname));

        FLPtoEPN messagei;

        FairMQMessagePtr aMessage = myRecvChan.NewMessage();
        myRecvChan.Receive(aMessage);
        std::memcpy(&messagei, aMessage->GetData(), sizeof(FLPtoEPN));
        if(aMessage->GetData(), &messagei, sizeof(FLPtoEPN)){
            LOG(info) << "Epn1 received data: " <<messagei.IdOfEpnReceivingData << endl;

            float x = getDelay();
            LOG(INFO) << "Delay work for:" << x << "seconds\n" << endl;
            std::thread t3(MyDelayedFun, x, &freeSlots);
            t3.detach();
         }
    }





void epn::send(int* memory, char* chan, uint64_t* numepns, int* id){
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

thread epn::senderThread(int* memory, char* chan, uint64_t* numepns, int* id) {
          return std::thread([=] {
          this->send(memory,chan,numepns,id);
          });
      }

void epn:: MyDelayedFun(float delayWork, int* memory){
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
