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

{
}

void flp::InitTask()
{

    arrayofEpns = new int[1];
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
            SchedFLPTest msgIReceive;

            //receive a message
            FairMQMessagePtr aMessage = myRecvChan.NewMessage();
            myRecvChan.Receive(aMessage);
            //get the pointer of the message.

            std::memcpy(&msgIReceive, aMessage->GetData(), sizeof(SchedFLPTest));
            if(aMessage->GetSize() ==sizeof(SchedFLPTest)){
            LOG(info) << "Received table of epns: "  << endl;
            LOG(info) << "The first EPN we need to send messages to has id: " << msgIReceive.IdForFirst << endl;
            arrayofEpns[0]=msgIReceive.IdForFirst;
            /*
            LOG(info) << "The second EPN we need to send messages to has id : " << msgIReceive.IdForSecondEpn << endl;
            arrayofEpns[1]=msgIReceive.IdForSecondEpn;
            LOG(info) << "The third EPN we need to send messages to has id : " << msgIReceive.IdForThirdEpn << endl;
            arrayofEpns[2]=msgIReceive.IdForThirdEpn;
            LOG(info) << "The fourth EPN we need to send messages to has id : " << msgIReceive.IdForFourthEpn << endl;
            arrayofEpns[3]=msgIReceive.IdForFourthEpn;
            */

            counter=0;



           //this_thread::sleep_for(chrono::seconds(2));

        }
        }

        if (poller->CheckOutput("data1", 0))
        {
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
            }
            }






/*
        if (poller->CheckOutput("data2", 0))
        {
            if(arrayofEpns[counter]==2){
                counter++;
                if(counter==4){
                  counter=-1;
                }



            auto &mySendingChan = GetChannel("data2");
            //the message I want to send
            FLPtoEPN MsgFlpEpn;
            MsgFlpEpn.IdOfEpnReceivingData = 2;



            FairMQMessagePtr message = mySendingChan.NewMessage(sizeof(FLPtoEPN));
            std::memcpy(message->GetData(), &MsgFlpEpn, sizeof(FLPtoEPN));

            mySendingChan.Send(message);

            LOG(info) << "Sent to Epn2 \"" << MsgFlpEpn.IdOfEpnReceivingData << "\"";
            }



            }




            if (poller->CheckOutput("data3", 0))
        {
            if(arrayofEpns[counter]==3){
                counter++;
                if(counter==4){
                  counter=-1;
                }




            auto &mySendingChan = GetChannel("data3");
            //the message I want to send
            FLPtoEPN MsgFlpEpn;
            MsgFlpEpn.IdOfEpnReceivingData = 3;



            FairMQMessagePtr message = mySendingChan.NewMessage(sizeof(FLPtoEPN));
            std::memcpy(message->GetData(), &MsgFlpEpn, sizeof(FLPtoEPN));

            mySendingChan.Send(message);

            LOG(info) << "Sent to Epn3 \"" << MsgFlpEpn.IdOfEpnReceivingData << "\"";
            }


            }




            if (poller->CheckOutput("data4", 0))
        {
            if(arrayofEpns[counter]==4){
                counter++;
                if(counter==4){
                  counter=-1;
                }



            auto &mySendingChan = GetChannel("data4");
            //the message I want to send
            FLPtoEPN MsgFlpEpn;
            MsgFlpEpn.IdOfEpnReceivingData = 4;
            FairMQMessagePtr message = mySendingChan.NewMessage(sizeof(FLPtoEPN));
            std::memcpy(message->GetData(), &MsgFlpEpn, sizeof(FLPtoEPN));

            mySendingChan.Send(message);

            LOG(info) << "Sent to Epn4 \"" << MsgFlpEpn.IdOfEpnReceivingData << "\"";
            }




        }
        */
    }
}



flp::~flp()
{
    if(arrayofEpns)
        delete[] arrayofEpns;

}
}
