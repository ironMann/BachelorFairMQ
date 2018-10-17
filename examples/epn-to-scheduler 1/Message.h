/* Message.h */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "/home/charlotte/fairmq/fairmq/FairMQDevice.h"

namespace epn_to_scheduler
{



       struct EPNtoScheduler{int Id; uint64_t freeSlots; uint64_t numEPNs; float interval;};

  

}


#endif
