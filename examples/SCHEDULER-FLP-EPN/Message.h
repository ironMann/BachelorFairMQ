/* Message.h */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include "/home/charlotte/fairmq/fairmq/FairMQDevice.h"
#include <vector>

namespace example_SCHEDULER_FLP_EPN
{



       struct EPNtoScheduler{int Id; uint64_t freeSlots; uint64_t numEPNs;};
       struct SchedulerToFLP{int IdForFirstEpn; int IdForSecondEpn; int IdForThirdEpn;};
       struct FLPtoEPN{unsigned long IdOfTF; int IdOfFlp;};

       struct SchedFLPTest{int IdForFirst;};


}


#endif
