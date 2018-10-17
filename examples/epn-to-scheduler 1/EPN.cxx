#include <thread> // this_thread::sleep_for
#include <chrono>
#include <type_traits>

#include "EPN.h"
#include "Message.h"


using namespace std;

namespace epn_to_scheduler
{

EPN::EPN()
    : Id(0)
    , freeSlots(0)
    , interval(0)
    , numEPNs(0)
{
static_assert(std::is_pod<EPNtoScheduler>::value==true, "my struct is not pod");
}

void EPN::InitTask()
{
    // Get the ID, the free Slots and the millisecond values from the command line options (via fConfig)
    Id = fConfig->GetValue<int>("myid");
    freeSlots = fConfig->GetValue<uint64_t>("freeSlots");
    interval = fConfig->GetValue<float>("interval");
    numEPNs = fConfig->GetValue<uint64_t>("numEPNS");


    
}

bool EPN::ConditionalRun()
{
    sender();
    //sleep(1);
    return true;
}

void EPN::sender()
{

  auto &mySendingChan = GetChannel("data");


  // the message I want to send
  EPNtoScheduler myMsg;
  myMsg.Id = Id;
  myMsg.freeSlots = freeSlots;
  myMsg.numEPNs = numEPNs;
  myMsg.interval = interval;

  // create message for sending
  FairMQMessagePtr message = mySendingChan.NewMessage(sizeof(EPNtoScheduler));
  // copy your data into the FairMQ message
  std::memcpy(message->GetData(), &myMsg, sizeof(EPNtoScheduler));
  // send the message
  mySendingChan.Send(message);

  LOG(INFO)<<"sent ID: "<<myMsg.Id<<" and amount of free slots  "<<myMsg.freeSlots<< " general amount of EPNs: " <<myMsg.numEPNs << " sent in the interval of: " <<myMsg.interval<<" ms. ";


}
/*
float EPN::convert(float intervall)
{
    float a;
    float b= 1000;
    a=b/intervall;
    return a;
    }
    */
EPN::~EPN()
{
}

} // namespace epn_to_scheduler
