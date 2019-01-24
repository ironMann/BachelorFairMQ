

#include "runFairMQDevice.h"
#include "scheduler.h"

namespace bpo = boost::program_options;

void addCustomOptions(bpo::options_description& options) {
  options.add_options()("numEPNS", bpo::value<uint64_t>()->default_value(43), "number of EPNs")(
      "numFLPS", bpo::value<uint64_t>()->default_value(0), "number of Flps")(
      "amountEPNs", bpo::value<uint64_t>()->default_value(0), "the number of EPNs in the schedule")(
      "programTime", bpo::value<uint64_t>()->default_value(1), "time of the program");
}

FairMQDevicePtr getDevice(const FairMQProgOptions& /*config*/) { return new example_SCHEDULER_FLP_EPN::scheduler(); }
