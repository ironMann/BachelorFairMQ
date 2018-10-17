#include <thread> // this_thread::sleep_for
#include <chrono>
#include <type_traits>

#include "FLP.h"
#include "Message.h"


using namespace std;

namespace epn_to_scheduler
{

FLP::FLP()

{
static_assert(std::is_pod<EPNtoScheduler>::value==true, "my struct is not pod");
}

void FLP::InitTask()
{    
}

bool FLP::ConditionalRun()
{
    receive();
    return true;
}

void FLP::receive()
{

  auto &myRecvChan = GetChannel("data1");



  EPNtoScheduler FLPMsg;

  FairMQMessagePtr message = myRecvChan.NewMessage();
  myRecvChan.Receive(message);
  std::memcpy(&FLPMsg, message->GetData(), sizeof(EPNtoScheduler));


  LOG(INFO)<<"received ID: "<<FLPMsg.Id<<" and amount of free slots  "<<FLPMsg.freeSlots<< " general amount of EPNs: " <<FLPMsg.numEPNs << " sent in the interval of: " <<FLPMsg.interval<<" ms. ";


}

FLP::~FLP()
{
}

} // namespace epn_to_scheduler
