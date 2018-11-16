
/**
 * scheduler.h
 *
 *
 */

#ifndef FAIRMQEXAMPLESCHEDULERFLPEPNSCHEDULER_H
#define FAIRMQEXAMPLESCHEDULERFLPEPNSCHEDULER_H

#include "FairMQDevice.h"
#include "Message.h"
#include <string>
#include <map>
#include <vector>
#include <chrono>
#include <thread>

namespace example_SCHEDULER_FLP_EPN
{

class scheduler : public FairMQDevice
{
  public:
    scheduler();
    virtual ~scheduler();
    void sender(std::vector<uint64_t>* vec, uint64_t* num, uint64_t* numE, uint64_t* schedNum);

  protected:
  //for EPN SCHEDULER DEALING
    struct EpnInfo {uint64_t ts = 0; uint64_t memVal = 0;};
    std::map<uint64_t,std::vector<EpnInfo> > history;
    uint64_t numEPNS;
    uint64_t numFLPS;
    const unsigned intMs;
    const unsigned aliveTimeMs;
    const unsigned historyMaxMs;
    std::vector<uint64_t>  sched;

       //constants to generate array sent to FLPs
    const unsigned amountSubtimeframes; //the amount of subtimeframes the FLPs send to the EPNs per second
    uint64_t amountEPNs; //amount of EPNs that are in the array the Scheduler needs to send to the FLPs
    const float intervalFLPs; // the interval in seconds in which the scheduler needs to send array to all FLPs

  //for SCHEDULER FLP DEALING
    int* arrayForFlps; //just declare a



    //needed for history processing
    uint64_t tooOld; //key which is tooOld (timestamp)
    uint64_t keyForToFile; // reference key for writing history to File
    uint64_t keyForGeneratingArray; //reference key for generating the array
    uint64_t scheduleNumber;
    int m;

    std::thread senderThread(std::vector<uint64_t>* vec, uint64_t* num, uint64_t* numE, uint64_t* schedNum);



    virtual bool ConditionalRun() override;
    virtual void InitTask() override;
    uint64_t getHistKey();
    void initialize(uint64_t numEPNs);
    void printHist();
    void update(uint64_t epnId, uint64_t myMem);
    void toFile();
    //what I want to return in this function is a pointer to the first element of the array
    int* generateArray();
    int maxSearch(int arr[]); // find the EPN with the most free memory, returns the index of the EPN with most free memory
    void printArrFLP(int arr[], int length);
    void printfreeSlots(int arr[], int length);
    std::vector<uint64_t> simpleRRSched(int m); //function to print the array that will be sent to all FLPs



};

}

#endif /* FAIRMQEXAMPLESCHEDULERFLPEPNSCHEDULER_H */
