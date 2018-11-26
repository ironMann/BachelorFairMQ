/*
 * scheduler.cpp
 *
 */

#include <thread> // this_thread::sleep_for
#include <chrono>
#include <memory>
#include "scheduler.h"
#include "Message.h"
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

using namespace std;

namespace example_SCHEDULER_FLP_EPN
{

scheduler::scheduler()
          :history()
          ,numEPNS(0)
          ,numFLPS(0)
          ,intMs(1000) //one second
          ,progTime(60*1*intMs)//alive time of the program
          ,historyMaxMs(60*20*intMs)//one minute
          ,sched()
          ,msBetweenSubtimeframes(2)
          ,amountEPNs(0)
          ,intervalFLPs(0.5)
          ,arrayForFlps(0)
          ,tooOld(0)
          ,keyForToFile(0)
          ,keyForGeneratingArray(0)
          ,keyForExiting(0)
          ,scheduleNumber(0)
          ,m(1) //what the hell is m for? It's for the round robin thing
{
}

void scheduler::InitTask(){
    numEPNS = fConfig->GetValue<uint64_t>("numEPNS");
    numFLPS=fConfig->GetValue<uint64_t>("numFLPS");
    amountEPNs=fConfig->GetValue<uint64_t>("amountEPNs");
    keyForToFile = getHistKey();
    keyForGeneratingArray=getHistKey();
    keyForExiting=getHistKey();
    initialize(numEPNS);
    printHist();
    arrayForFlps = new int[amountEPNs];

}


bool scheduler::ConditionalRun()
{
  //FairMQPollerPtr poller(NewPoller("epnsched"));
  //poller->Poll(1000);
    if((getHistKey()-keyForExiting)>progTime){
      LOG(INFO)<<"TERMINATING PROGRAM NOW!";
      ChangeState("READY");
      ChangeState("RESETTING_TASK");
      ChangeState("DEVICE_READY");
      ChangeState("RESETTING_DEVICE");
      ChangeState("IDLE");
      ChangeState("EXITING");
    }
    else{
      for(uint64_t i=0; i < numEPNS; i++){
      //if (!poller->CheckInput("epnsched", i)) {
        //continue;
      //}

        auto &myRecvChan = GetChannel("epnsched",i);
        // I expect this kind of messages
        EPNtoScheduler msgFromSender;
        // receive a message
        FairMQMessagePtr aMessage = myRecvChan.NewMessage();
        if((getHistKey()-keyForExiting)>progTime){
              LOG(INFO)<<"TERMINATING PROGRAM NOW!";
              ChangeState("READY");
              ChangeState("RESETTING_TASK");
              ChangeState("DEVICE_READY");
              ChangeState("RESETTING_DEVICE");
              ChangeState("IDLE");
              ChangeState("EXITING");
            }
            else{
        myRecvChan.Receive(aMessage);
        // get the data of the FairMQ message
        std::memcpy(&msgFromSender, aMessage->GetData(), sizeof(EPNtoScheduler));
        if(aMessage->GetSize() == sizeof(EPNtoScheduler)){
        LOG(INFO)<<"received ID: "<<msgFromSender.Id<<" and amount of free slots "<<msgFromSender.freeSlots<<" and amount of EPNs is: "<< msgFromSender.numEPNs << endl;
        update(msgFromSender.Id, msgFromSender.freeSlots);
        printHist();
        }
      }
    }

    uint64_t localkey= getHistKey();
    if((localkey>=(keyForGeneratingArray + intervalFLPs*intMs))&&((localkey-keyForExiting)<progTime)){
        //sched=simpleRRSched(m);
        ofstream file, filem;
        file.open("availableEpns.txt", std::ios_base::app);
        file<<availableEpns(generateArray1())<<endl;
        filem.open("EpnsInSchedule.txt",std::ios_base::app);
        filem<<EpnsInSchedule(availableEpns(generateArray1()))<<endl;
        arrayForFlps = generateSchedule();
        sched = vector<uint64_t> (amountEPNs,(uint64_t) 0);
        sched.assign(arrayForFlps, arrayForFlps+amountEPNs);
        //m=(m+amountEPNs)%numEPNS;
        keyForGeneratingArray = localkey;
        printArrFLP(arrayForFlps, amountEPNs);
        scheduleNumber++;
        std::thread t1= senderThread(&sched, &numFLPS, &amountEPNs, &scheduleNumber);
        t1.detach();
        }

    else{
      LOG(INFO)<<"TERMINATING PROGRAM NOW!";
      ChangeState("READY");
      ChangeState("RESETTING_TASK");
      ChangeState("DEVICE_READY");
      ChangeState("RESETTING_DEVICE");
      ChangeState("IDLE");
      ChangeState("EXITING");



    }


    return true;

  }
}




thread scheduler::senderThread(std::vector<uint64_t>* vec, uint64_t* num, uint64_t* numE, uint64_t* schedNum){
    return std::thread([=]{
    this->sender(vec, num, numE, schedNum);
  });
}



uint64_t scheduler::getHistKey(){
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

void scheduler::initialize(uint64_t numberofEPNs){
    //history is empty
    //get my key
    const auto key = getHistKey();

    if (history.count(key) == 0) {
        history.insert(pair<uint64_t, vector<EpnInfo>> (key, vector<EpnInfo> (numberofEPNs)));
    }
}

void scheduler::printHist() {

    for (auto &keyVal : history) {
        //const auto Key = keyVal.first;
        const auto &Epns = keyVal.second;

        //std::cout << "TimeInterval: " << Key << endl;
        for(auto &epnI : Epns) {
            cout << epnI.ts << ":" << epnI.memVal << " ";
        }
    }
    cout << endl;
}

void scheduler::update(uint64_t epnId, uint64_t myMem) {
    // get the key (also current time)
    const auto key = getHistKey();

    //checking if the key already exists
    if(history.count(key) != 0) {
        history[key].at(epnId-1).ts = key;
        history[key].at(epnId-1).memVal = myMem;
    }
    //case that key does not exist.
    else{//get the previous key
        auto prevKey = history.rbegin();
        uint64_t prevKeyInt = prevKey->first;

            //insert a new vector
            history.insert(pair<uint64_t, vector<EpnInfo>> (key, vector<EpnInfo> (numEPNS)));

            //copy the old values in the new vector
            for(uint64_t a = 0; a < numEPNS; a++ ) {
                //check if EPN did get lost.
                if(history[prevKeyInt].at(a).ts < tooOld){
                    history[key].at(a).ts = 0;
                    history[key].at(a).memVal=0;
                    }
                else{
                history[key].at(a).ts=history[prevKeyInt].at(a).ts;
                history[key].at(a).memVal=history[prevKeyInt].at(a).memVal;
                }
           }

            //overwrite with the current values.
            history[key].at(epnId-1).ts = key;
            history[key].at(epnId-1).memVal = myMem;

       // }
    }
    // check if the history should be trimmed
    //get first key
    auto firstKey = history.begin();
    tooOld = (*firstKey).first;
        while(key>=(tooOld+historyMaxMs)){
            //delete the first key.
            history.erase(firstKey);
            auto newFirstKey = history.begin();
            //update tooOld integer
            tooOld =  newFirstKey->first;
        }
        //write history to file every minute.
    if(key >= (keyForToFile + historyMaxMs)){
        toFile();
        keyForToFile = key;
        }
        //generate array every 2 seconds.







}


void scheduler::toFile(){
    ofstream myfile;
    myfile.open("heatdata.txt", std::ios_base::app);
    for(auto a = history.begin(); a != history.end(); a ++ ){
        for(uint64_t i = 0; i < (numEPNS-1); i++){
            myfile << history[(*a).first].at(i).memVal << ", ";

        }
        myfile << history[(*a).first].at(numEPNS-1).memVal << endl;
    }
}


int* scheduler::generateSchedule(){
    int* temporaryStorage= generateArray1(); //pointer to array of amount of EPNs which we need to store the memory size of the valid EPNs
    int* desFLPsPointer = new int[amountEPNs]; // pointer to the array which the function will give back and contains the IDs of the EPNs that the FLPs need to send their subtimeframes to, beginning from the lowest ID and then in ascending order...

    //printfreeSlots(temporaryStorage, 1);
    //using maxSearchFunction the size of "amountEPNs" times to get the Ids of the EPNs with the highest memory capacities
    for(uint64_t i = 0; i < amountEPNs; i++){
        int maxIndex = maxSearch(temporaryStorage);
        desFLPsPointer[i]=maxIndex; //index of the EPNs with most memory capacity
    }

    return desFLPsPointer;
    if(temporaryStorage)
        delete[] temporaryStorage;
    if(desFLPsPointer)
        delete[] desFLPsPointer;
}

int* scheduler::generateArray1(){
  int*temporaryStorage=new int[numEPNS];

  auto latestKey = history.rbegin();
  //checking whether the EPNs are valid
  for(uint64_t i = 0; i < numEPNS; i++){
      if((*latestKey).first == history[(*latestKey).first].at(i).ts){
          temporaryStorage[i]= history[(*latestKey).first].at(i).memVal; //writing the memory values of the valid EPns in array
      }
      else{ //setting the other values to -1
          temporaryStorage[i]=-1;
      }
  }
  return temporaryStorage;
  if(temporaryStorage)
    delete[] temporaryStorage;
}

int scheduler::maxSearch(int arr[]){
    int max = arr[0];
    int index = 0;
    for(uint64_t i=1;i < numEPNS; i++){
        if(max < arr[i]){
            max = arr[i];
            index = i;
        }
    }
    if(arr[index]==-1){
        return -1;
    }
    else{
    arr[index]=-1;
    return index+1;
    }
}

void scheduler::printArrFLP(int arr[], int length){
     for (int n=0; n<length; ++n)
    cout << "Printing the array for the flps. number: "<< n+1<<" goes to: "<< arr[n] <<endl;
}


void scheduler::printfreeSlots(int arr[], int length){
       for (int n=0; n<length; ++n)
      cout << "free Slots: "<< arr[n] << ' ';
    cout << '\n';
  }



void scheduler::sender(std::vector<uint64_t>* vec, uint64_t* num, uint64_t* numE, uint64_t* schedNum){
    cout<<"number of FLPS: "<< (*num) << endl;
    for(uint64_t i=0; i<(*num); i++){
      auto &mySendingChan = GetChannel("schedflp", i);

      FairMQMessagePtr message = mySendingChan.NewMessage((sizeof(uint64_t))*(*numE));


      std::memcpy(message->GetData(), vec->data(), (sizeof(uint64_t))*(*numE));
      mySendingChan.Send(message);

      for(vector<uint64_t>::const_iterator iter = vec->begin(); iter!=vec->end(); ++iter){

        LOG(INFO)<<"Schedule number "<< *schedNum<<" sent Id of epn which is: "<< *iter;
      }


    }
}

int scheduler::availableEpns(int arr[]){
  int c=0;
  for(uint64_t i=0;i<numEPNS;i++){
    if(arr[i]>0){
      c++;
    }
  }
  return c;
}


int scheduler::EpnsInSchedule(int aE){
  if(aE>=amountEPNs){
    return amountEPNs;
  }
  else{
    return aE;
  }
}

std::vector<uint64_t> scheduler::simpleRRSched(int m){
  std::vector<uint64_t> roundr;
  for(int j=m; j<(m+amountEPNs);j++){
    roundr.push_back(j);
  }
  return roundr;

}
/*
simpleRRSched()

  static EPNtosend - 0


  epn = epn +1 mod% (numepns)
  */





scheduler::~scheduler()
{
    if(arrayForFlps)
        delete[] arrayForFlps;

}

}//namespace SCHEDULER_FLP_EPN
