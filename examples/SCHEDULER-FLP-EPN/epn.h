/**
 * epn.h
 *
 *
 *
 */

#ifndef FAIRMQEXAMPLESCHEDULERFLPEPNEPN_H
#define FAIRMQEXAMPLESCHEDULERFLPEPNEPN_H

#include "FairMQDevice.h"
#include "Message.h"
#include <iostream>
#include <string>
#include <random>
#include <thread>




namespace example_SCHEDULER_FLP_EPN
{

class epn : public FairMQDevice
{
  public:
    epn();
    virtual ~epn();
    void send(uint64_t* memory, uint64_t* numepns, int* id);


  protected:
    int Id;
    uint64_t freeSlots;
    uint64_t maxSlots;
    uint64_t numEPNS;
    uint64_t numFLPS;
    std::map<int,int> rcvdSTFs;
    int sTF;

    const float procTime;
    const float procDev;

    char channelname;
    const std::string channel;




    virtual void InitTask();
    virtual bool ConditionalRun();

    std::string getChannel(char number);
    void receive();

    bool checkFLP();
    void rcvdSTFsToFile();

    std::thread senderThread(uint64_t* memory, uint64_t* numepns, int* id);


    static void MyDelayedFun(float delayWork, uint64_t* memory);
    float getDelay();





};

}

#endif /* FAIRMQEXAMPLESCHEDULERFLPEPNEPN_H */
