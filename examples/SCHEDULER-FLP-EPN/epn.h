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
#include <time.h>
#include <iostream>
#include <string>
#include <random>
#include <thread>
#include <sstream>




namespace example_SCHEDULER_FLP_EPN
{

class epn : public FairMQDevice
{
  public:
    epn();
    virtual ~epn();
    void send(int* memory, uint64_t* numepns, uint64_t* id, uint64_t* start,const uint64_t* max);


  protected:
    uint64_t Id;
    int freeSlots;
    uint64_t maxSlots;
    uint64_t numEPNS;
    uint64_t numFLPS;
    std::map<unsigned long,int> rcvdSTFs;
    std::map<unsigned long,int>::iterator it;
    int sTF;

    const float procTime;
    const float procDev;

    uint64_t startTime;
    uint64_t timeBetweenTf;
    uint64_t programTime; //the duration of the program.
    const unsigned intMs;

    std::stringstream receptionOfTf1;
    std::stringstream processingTime1;






    virtual void InitTask();
    virtual bool ConditionalRun();

    std::string getChannel(char number);
    void receive();



    std::thread senderThread(int* memory, uint64_t* numepns, uint64_t* id, uint64_t* start,const uint64_t* max);


    static void MyDelayedFun(float delayWork, int* memory, std::stringstream* procTime);
    float getDelay();

    uint64_t getHistKey();







};

}

#endif /* FAIRMQEXAMPLESCHEDULERFLPEPNEPN_H */
