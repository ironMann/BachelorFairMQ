#include "runFairMQDevice.h"
#include "epn.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options)
{
    options.add_options()
        ("myId", bpo::value<uint64_t>()->default_value(377), "ID")
        ("maxSlots", bpo::value<uint64_t>()->default_value(3), "amount of free Slots")
        ("numEPNS", bpo::value<uint64_t>()->default_value(43), "number of EPNs")
        ("numFLPS", bpo::value<uint64_t>()->default_value(1), "amount of Flps")
        ("programTime", bpo::value<uint64_t>()->default_value(1), "time of the program");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/)
{
    return new example_SCHEDULER_FLP_EPN::epn();
}
