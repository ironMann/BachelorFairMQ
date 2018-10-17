#include "Scheduler.h"
#include "Message.h"
#include <string>

using namespace std;

namespace epn_to_scheduler
{

Scheduler::Scheduler()
    
{
    OnData("data", &Scheduler::HandleData);
}  



bool Scheduler::HandleData(FairMQMessagePtr& msg, int /*index*/){
    
    receive();
    return true;
    }

// 'receiver' device
void Scheduler::receive() {
  auto &myRecvChan = GetChannel("data");
  
  // I expect this kind of messages
  EPNtoScheduler msgFromSender;
  
  // receive a message
  FairMQMessagePtr aMessage = myRecvChan.NewMessage();
  myRecvChan.Receive(aMessage);
  // get the data of the FairMQ message
  //assert(aMessage->GetSize() == sizeof(EPNtoScheduler));
  std::memcpy(&msgFromSender, aMessage->GetData(), sizeof(EPNtoScheduler));
  

  
  LOG(INFO)<<"received ID: "<<msgFromSender.Id<<" and amount of free slots "<<msgFromSender.freeSlots<<" and amount of EPNs is: "<< msgFromSender.numEPNs <<" sent in the interval of: "<<msgFromSender.interval<<" ms. ";
  

  
  
}


Scheduler::~Scheduler()
{
}

} // namespace epn_to_scheduler
