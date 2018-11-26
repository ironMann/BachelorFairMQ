/**
 * flp.cpp
 *
 */

#include <memory> // unique_ptr
#include <thread> // this_thread::sleep_for
#include <chrono>


#include "flp.h"
#include "FairMQPoller.h"
#include "Message.h"

using namespace std;

namespace example_SCHEDULER_FLP_EPN
{

flp::flp()
    : arrayofEpns()
    , msBetweenSubtimeframes(1000)
    , amountEPNs(0)
    , numEPNS(0)
    , socket(0)
    , myId(0)
    , sTF(0)
    , startTime(0)
    , progTime(60*2*1000)

{
}

void flp::InitTask()
{
    amountEPNs = fConfig->GetValue<int>("amountEPNs");
    numEPNS= fConfig->GetValue<uint64_t>("numEPNS");
    socket = fConfig->GetValue<int>("socket");
    myId = fConfig->GetValue<int>("myId");
    arrayofEpns = new int[amountEPNs];
    startTime=getHistKey();
}

void flp::Run()
{
    while (CheckCurrentState(RUNNING)) //
    {
      if(getHistKey()-startTime>=progTime){
        LOG(INFO)<<"TERMINATING PROGRAM NOW!";
        ChangeState("READY");
        ChangeState("RESETTING_TASK");
        ChangeState("DEVICE_READY");
        ChangeState("RESETTING_DEVICE");
        ChangeState("IDLE");
        ChangeState("EXITING");
      }

      else{
            auto &myRecvChan = GetChannel("schedflp");
            //I expect this kind of message
            std::vector<uint64_t> msgIReceive (amountEPNs, 0);


            //receive a message
            FairMQMessagePtr aMessage = myRecvChan.NewMessage();
            myRecvChan.Receive(aMessage);
            //get the pointer of the message.

            std::memcpy(msgIReceive.data(), aMessage->GetData(), ((sizeof(uint64_t))*amountEPNs));
            if(aMessage->GetSize() ==((sizeof(uint64_t))*amountEPNs)){
              int i=0;
              for(vector<uint64_t>::const_iterator iter = msgIReceive.begin(); iter != msgIReceive.end(); ++iter){
              LOG(info) << "Subtimeframe goes to EPN number: "<< (*iter);
              arrayofEpns[i]=*iter;
              LOG(info)<<"wrote in arrayofEPns["<<i<<"]: " << arrayofEpns[i];
              i++;


            }

          }


        for(int i=0; i<amountEPNs; i++){
            sTF++;
            int c = arrayofEpns[i];
            cout << "arrayofEpns["<<i<<"]: " <<c<<endl;
            cout<<"socket number, where it gets sent to:" << (c-1) << " and the STF is: "<< sTF<< endl;
            auto &mySendingChan = GetChannel("data", (c-1));
            //the message I want to send
            FLPtoEPN MsgFlpEpn;
            MsgFlpEpn.IdOfFlp = myId;
            MsgFlpEpn.sTF = sTF;



            FairMQMessagePtr message = mySendingChan.NewMessage(sizeof(FLPtoEPN));
            std::memcpy(message->GetData(), &MsgFlpEpn, sizeof(FLPtoEPN));

            mySendingChan.Send(message);

            LOG(info) << "Sent to Epn \"" << c << " and subtimeframe: "<<MsgFlpEpn.sTF<< " and my Id is: "<< MsgFlpEpn.IdOfFlp<< "\"";
            std::this_thread::sleep_for(std::chrono::milliseconds(msBetweenSubtimeframes)); //wait 20 ms.
            }


      }
    }
}

uint64_t flp::getHistKey(){
    //get the current time
    const auto time = std::chrono::high_resolution_clock::now();
    //get the time from THEN to now
    auto duration = time.time_since_epoch();
    const std::uint64_t millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

    //std::cout << "Milliseconds : " << millis << std::endl;
    //determine the interval (key for the hist map)
    const std::uint64_t intKey = millis / 1000 * 1000;
    //cout<< "histKey : " << intKey << endl;

    return intKey;

}



flp::~flp()
{
    if(arrayofEpns)
        delete[] arrayofEpns;

}
}
