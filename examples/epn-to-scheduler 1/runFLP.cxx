#include "/home/charlotte/fairmq/fairmq/runFairMQDevice.h"
#include "FLP.h"


namespace bpo = boost::program_options;


void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
    /*
        ("myid", bpo::value<int>()->default_value(377), "ID")
        ("freeSlots", bpo::value<uint64_t>()->default_value(0), "amount of free Slots")
        ("numEPNS", bpo::value<uint64_t>()->default_value(43), "number of EPNs")
        ("interval", bpo::value<float>()->default_value(30), "milliseconds until next update");
        */

  }




FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new epn_to_scheduler::FLP();
    }
