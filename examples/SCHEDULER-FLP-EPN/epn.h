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
    void send(int* memory, char* chan, uint64_t* numepns, int* id);
    
    
  protected:
    int Id;
    int freeSlots;
    int amountFlps;
    uint64_t maxSlots;
    uint64_t numEPNS;
    
    const float procTime;
    const float procDev;
    
    char channelname;
    const std::string channel;
    



    virtual void InitTask();
    virtual bool ConditionalRun();
    
    std::string getChannel(char number);
    void receive();
    
    std::thread senderThread(int* memory, char* chan, uint64_t* numepns, int* id);


    static void MyDelayedFun(float delayWork, int* memory);
    float getDelay();
    




};

}

#endif /* FAIRMQEXAMPLESCHEDULERFLPEPNEPN_H */
