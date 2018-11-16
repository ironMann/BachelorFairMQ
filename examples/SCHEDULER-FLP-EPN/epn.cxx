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
    ,rcvdSTFs()
    ,sTF(1)
    ,it()
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
        std::thread th1 = senderThread(&freeSlots, &numEPNS, &Id);
        th1.detach();

    }


bool epn::ConditionalRun()
{

     receive();


return true;



}

void epn::receive(){
        FairMQPollerPtr poller(NewPoller("data"));
        poller->Poll(100);


        for(uint64_t i=0; i<numFLPS; i++){

          if (!poller->CheckInput("data", i)) {
            continue;
          }

          auto &myRecvChan = GetChannel("data", i);

          FLPtoEPN messagei;

          FairMQMessagePtr aMessage = myRecvChan.NewMessage();

          if (sizeof(FLPtoEPN) != myRecvChan.Receive(aMessage)) {
            LOG(ERROR) << "Bad Message from FLP" << i+1;
            continue;
          }

          std::memcpy(&messagei, aMessage->GetData(), sizeof(FLPtoEPN));

          if (messagei.IdOfFlp != (i+1)) {
            LOG(ERROR) << "Bad Message ID from FLP" << i+1 << " != " << messagei.IdOfFlp;
            continue;
          }



          rcvdSTFs[messagei.sTF]++;
          if(rcvdSTFs[messagei.sTF] == numFLPS){
            LOG(info) << "Epn received data from FLP number: " << messagei.IdOfFlp << " and sTF number is "<< messagei.sTF;
          }
          /*
          for( it=rcvdSTFs.begin(); it!=rcvdSTFs.end(); it++){
            cout<< it->first<<" =>"<< it->second<<endl;
          }
          */
          assert(rcvdSTFs[messagei.sTF] <= numFLPS);

          if(rcvdSTFs[messagei.sTF] == numFLPS){
            freeSlots--;

            if(freeSlots>=0) {
              float x = getDelay();
              LOG(INFO) << "Delay work for: " << x << "seconds for TFid: " << messagei.sTF;
              std::thread t3(MyDelayedFun, x, &freeSlots);
              t3.detach();
            } else {
              LOG(info)<<"INFORMATION LOST DUE TO OVERCAPACITY.";
              freeSlots=0;
            }
          }
      }
    }






void epn::send(int* memory, uint64_t* numepns, int* id){
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

thread epn::senderThread(int* memory, uint64_t* numepns, int* id) {
          return std::thread([=] {
          this->send(memory,numepns,id);
          });

          // return std::thread(&epn::send, this, memory,numepns,id);
      }

void epn:: MyDelayedFun(float delayWork,int* memory){
     //(*memory)--;
     cout<<"amount of memory slots after decrementing: "<<*memory<<endl;
     std::this_thread::sleep_for(std::chrono::milliseconds(long  (delayWork*1000)));
     cout<<"Delayed thread executioning the work now! \n";
     (*memory)++;
}

float epn:: getDelay(){
     static std::default_random_engine generator;
     std::normal_distribution<float> distribution(procTime, procDev);
     float delay = distribution(generator);
     cout<<"Delay work for:" << delay <<"seconds\n";
     return delay;
}







epn::~epn()
{
}

}
