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
#include <time.h>
#include <fstream>
#include <sstream>



using namespace std;

namespace example_SCHEDULER_FLP_EPN
{

epn::epn()
    : Id(0)
    , freeSlots(0)
    , maxSlots(4)
    , numEPNS()
    , numFLPS(0)
    , rcvdSTFs()
    , it()
    , sTF(1)
    , procTime(10)
    , procDev(1)
    , startTime(0)
    ,timeBetweenTf(0)
    ,programTime(0)
    ,intMs(1000)
    ,receptionOfTf1()
    ,processingTime1()



    {
    static_assert(std::is_pod<EPNtoScheduler>::value==true, "my struct  is not pod");
    }

void epn::InitTask()
{
	timeBetweenTf=getHistKey();
        startTime=getHistKey();
        Id = fConfig->GetValue<int>("myId");
        maxSlots = 4;
        freeSlots = maxSlots;
        numEPNS = fConfig->GetValue<uint64_t>("numEPNS");
        numFLPS = fConfig->GetValue<uint64_t>("numFLPS");
        programTime = fConfig->GetValue<uint64_t>("programTime");
        programTime=programTime*60*1000;
        std::thread th1 = senderThread(&freeSlots, &numEPNS, &Id, &startTime, &programTime);
        th1.detach();


    }


bool epn::ConditionalRun()
{

  uint64_t currentTime=getHistKey();
  if(currentTime-startTime>=programTime){
    ofstream receptionOfTf, processingTime;
    static stringstream* all[3];

    all[Id-1]=&receptionOfTf1;

      receptionOfTf.open("TimebetweenReceptionOfTf.txt", std::ios_base::app);
      for (uint64_t a=0; a < numEPNS; a++){
        if(a==(Id-1)){
          LOG(INFO)<< ((*(all[a])).str());
          receptionOfTf<< ((*(all[a])).str());
          }
        else{
          std::this_thread::sleep_for(std::chrono::milliseconds(long  (1000)));

        }
    }


    static stringstream* all1[3];
    //string reception = receptionOfTf1.str();
    //cout<<reception<<endl;
    all1[Id-1]=&processingTime1;
    processingTime.open("processingTime.txt", std::ios_base::app);
      for (uint64_t a=0; a < numEPNS; a++){
        if(a==(Id-1)){
          LOG(INFO)<< ((*(all1[a])).str());
          processingTime<< ((*(all1[a])).str());
          }
        else{
          std::this_thread::sleep_for(std::chrono::milliseconds(long  (1000)));

        }
    }





    LOG(INFO)<<"TERMINATING PROGRAM NOW!";
    ChangeState("READY");
    ChangeState("RESETTING_TASK");
    ChangeState("DEVICE_READY");
    ChangeState("RESETTING_DEVICE");
    ChangeState("IDLE");
    ChangeState("EXITING");

  }
  else{
     receive();
     return true;
   }



}



uint64_t epn::getHistKey(){
    //get the current time
    const auto time = std::chrono::high_resolution_clock::now();
    //get the time from THEN to now
    auto duration = time.time_since_epoch();
    const std::uint64_t millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
    //std::cout << "Milliseconds : " << millis << std::endl;
    //determine the interval (key for the hist map)
    const std::uint64_t intKey = millis / intMs * intMs;
    //cout<< "histKey : " << intKey << endl;
    return intKey;

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
            receptionOfTf1<< (getHistKey()-timeBetweenTf) <<skipws<< endl;
            timeBetweenTf=getHistKey();
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
              std::thread t3(MyDelayedFun, x, &freeSlots, &processingTime1);
              t3.detach();
            } else {
              LOG(info)<<"INFORMATION LOST DUE TO OVERCAPACITY.";
              freeSlots=0;
            }
          }
      }
    }






void epn::send(int* memory, uint64_t* numepns, uint64_t* id, uint64_t* start,const uint64_t* max){
  //change the sending
        uint64_t now=getHistKey();
        while((now-(*start))< *max){
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
            now=getHistKey();
            }

}

thread epn::senderThread(int* memory, uint64_t* numepns, uint64_t* id, uint64_t* start,const uint64_t* max) {
          return std::thread([=] {
          this->send(memory,numepns,id,start, max);
          });

          // return std::thread(&epn::send, this, memory,numepns,id);
      }

void epn:: MyDelayedFun(float delayWork,int* memory, std::stringstream* procTime){
     //(*memory)--;
     cout<<"amount of memory slots after decrementing: "<<*memory<<endl;
     (*procTime) << delayWork << endl;
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
