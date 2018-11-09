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

{
}

void flp::InitTask()
{
    amountEPNs = fConfig->GetValue<unsigned>("amountEPNs");
    arrayofEpns = new int[amountEPNs];
}

void flp::Run()
{
    FairMQPollerPtr poller(NewPoller("data1", "schedflp")); //here we have a multiplexer that is channeling between all channels, we call it poller and we have two channels one where we send and one where we receive data

    while (CheckCurrentState(RUNNING)) //
    {
        poller->Poll(100);

        if (poller->CheckInput("schedflp", 0))
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
        }

          if(arrayofEpns[counter]==1){
              counter++;
              if(counter==1){
                counter=-1;
              }




            auto &mySendingChan = GetChannel("data1");
            //the message I want to send
            FLPtoEPN MsgFlpEpn;
            MsgFlpEpn.IdOfEpnReceivingData = 1;



            FairMQMessagePtr message = mySendingChan.NewMessage(sizeof(FLPtoEPN));
            std::memcpy(message->GetData(), &MsgFlpEpn, sizeof(FLPtoEPN));

            mySendingChan.Send(message);

            LOG(info) << "Sent to Epn1 \"" << MsgFlpEpn.IdOfEpnReceivingData << "\"";
            std::this_thread::sleep_for(std::chrono::milliseconds(msBetweenSubtimeframes)); //wait 20 ms.
            }

            if(arrayofEpns[counter]==2){
                counter++;
                if(counter==3){
                  counter=-1;
                }




              auto &mySendingChan = GetChannel("data2");
              //the message I want to send
              FLPtoEPN MsgFlpEpn;
              MsgFlpEpn.IdOfEpnReceivingData = 2;



              FairMQMessagePtr message = mySendingChan.NewMessage(sizeof(FLPtoEPN));
              std::memcpy(message->GetData(), &MsgFlpEpn, sizeof(FLPtoEPN));

              mySendingChan.Send(message);

              LOG(info) << "Sent to Epn \"" << MsgFlpEpn.IdOfEpnReceivingData << "\"";
              std::this_thread::sleep_for(std::chrono::milliseconds(msBetweenSubtimeframes)); //wait 20 ms.
              }

              if(arrayofEpns[counter]==3){
                  counter++;
                  if(counter==3){
                    counter=-1;
                  }




                auto &mySendingChan = GetChannel("data3");
                //the message I want to send
                FLPtoEPN MsgFlpEpn;
                MsgFlpEpn.IdOfEpnReceivingData = 3;



                FairMQMessagePtr message = mySendingChan.NewMessage(sizeof(FLPtoEPN));
                std::memcpy(message->GetData(), &MsgFlpEpn, sizeof(FLPtoEPN));

                mySendingChan.Send(message);

                LOG(info) << "Sent to Epn \"" << MsgFlpEpn.IdOfEpnReceivingData << "\"";
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
