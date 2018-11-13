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
    , counter(-1)
    , msBetweenSubtimeframes(20)
    , amountEPNs(0)
    , numEPNS(0)
    , socket(0)
    , myId(0)

{
}

void flp::InitTask()
{
    amountEPNs = fConfig->GetValue<int>("amountEPNs");
    numEPNS= fConfig->GetValue<uint64_t>("numEPNS");
    socket = fConfig->GetValue<int>("socket");
    cout << "socket number: "<< socket << endl;
    myId = fConfig->GetValue<int>("myId");
    arrayofEpns = new int[amountEPNs];
}

void flp::Run()
{
    while (CheckCurrentState(RUNNING)) //
    {


            auto &myRecvChan = GetChannel("schedflp");
            //I expect this kind of message
            SchedulerToFLP msgIReceive;

            //receive a message
            FairMQMessagePtr aMessage = myRecvChan.NewMessage();
            myRecvChan.Receive(aMessage);
            //get the pointer of the message.

            std::memcpy(&msgIReceive, aMessage->GetData(), sizeof(SchedulerToFLP));
            if(aMessage->GetSize() ==sizeof(SchedulerToFLP)){
              LOG(info) << "Received table of epns: "  << endl;
              LOG(info) << "The first EPN we need to send messages to has id: " << msgIReceive.IdForFirstEpn << endl;
              arrayofEpns[0]=msgIReceive.IdForFirstEpn;
              LOG(info) << "The second EPN we need to send messages to has id : " << msgIReceive.IdForSecondEpn << endl;
              arrayofEpns[1]=msgIReceive.IdForSecondEpn;
              LOG(info) << "The third EPN we need to send messages to has id : " << msgIReceive.IdForThirdEpn << endl;
              arrayofEpns[2]=msgIReceive.IdForThirdEpn;


              counter=0;





        }
        for(int i=0; i<amountEPNs; i++){ //finishing for loop
            int c = arrayofEpns[i];
            auto &mySendingChan = GetChannel("data", (c-1));
            //the message I want to send
            FLPtoEPN MsgFlpEpn;
            MsgFlpEpn.IdOfFlp = myId;



            FairMQMessagePtr message = mySendingChan.NewMessage(sizeof(FLPtoEPN));
            std::memcpy(message->GetData(), &MsgFlpEpn, sizeof(FLPtoEPN));

            mySendingChan.Send(message);

            LOG(info) << "Sent to Epn \"" << MsgFlpEpn.IdOfFlp << "\"";
            std::this_thread::sleep_for(std::chrono::milliseconds(msBetweenSubtimeframes)); //wait 20 ms.
            }


    }
}



flp::~flp()
{
    if(arrayofEpns)
        delete[] arrayofEpns;

}
}
