#include "runFairMQDevice.h"
#include "flp.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
      ("amountEPNs", bpo::value<int>()->default_value(0), "number of the EPNs in the schedule")
      ("numEPNS", bpo::value<uint64_t>()->default_value(0), "total number of EPNs")
      ("socket", bpo::value<int>()->default_value(0), "socket number")
      ("myId", bpo::value<int>()->default_value(0), "IdofFlp");

}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new example_SCHEDULER_FLP_EPN::flp();
}
