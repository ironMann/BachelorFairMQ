#!/bin/bash

export FAIRMQ_PATH=/home/charlotte/fairmq/fairmq

SchedulerFlpEpnconfig="/home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/ex-SCHEDULER-FLP-EPN.json"

FLP1="fairmq-ex-SCHEDULER-FLP-EPN-flp"
FLP1+=" --id flp1"
FLP1+=" --io-threads 4"
FLP1+=" --amountEPNs 3"
FLP1+=" --numEPNS 3"
FLP1+=" --socket 0"
FLP1+=" --myId 1"
FLP1+=" --mq-config $SchedulerFlpEpnconfig"
#FLP+=" --channel-config name=schedflp,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5557"
#FLP+="                  name=data1,type=push,method=bind,rateLogging=0,address=tcp://localhost:5556"
xterm -geometry 80x23+0+0 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$FLP1 &

FLP2="fairmq-ex-SCHEDULER-FLP-EPN-flp"
FLP2+=" --id flp2"
FLP2+=" --io-threads 4"
FLP2+=" --amountEPNs 3"
FLP2+=" --numEPNS 3"
FLP2+=" --socket 1"
FLP2+=" --myId 2"
FLP2+=" --mq-config $SchedulerFlpEpnconfig"
#FLP+=" --channel-config name=schedflp,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5557"
#FLP+="                  name=data1,type=push,method=bind,rateLogging=0,address=tcp://localhost:5556"
xterm -geometry 80x23+0+0 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$FLP2 &

FLP3="fairmq-ex-SCHEDULER-FLP-EPN-flp"
FLP3+=" --id flp3"
FLP3+=" --io-threads 4"
FLP3+=" --amountEPNs 3"
FLP3+=" --numEPNS 3"
FLP3+=" --socket 2"
FLP3+=" --myId 3"
FLP3+=" --mq-config $SchedulerFlpEpnconfig"
#FLP+=" --channel-config name=schedflp,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5557"
#FLP+="                  name=data1,type=push,method=bind,rateLogging=0,address=tcp://localhost:5556"
xterm -geometry 80x23+0+0 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$FLP3 &

EPN1="fairmq-ex-SCHEDULER-FLP-EPN-epn"
EPN1+=" --id epn1"
EPN1+=" --io-threads 4"
EPN1+=" --myId 1"
EPN1+=" --maxSlots 4"
EPN1+=" --numEPNS 3"
EPN1+=" --numFLPS 3"
EPN1+=" --mq-config $SchedulerFlpEpnconfig"
#EPN1+=" --channel-config name=epnsched,type=push,method=bind,rateLogging=0,address=tcp://localhost:5555"
#EPN1+=" --channel-config name=data1,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5556"
xterm -geometry 80x23+500+0 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$EPN1 &

EPN2="fairmq-ex-SCHEDULER-FLP-EPN-epn"
EPN2+=" --id epn2"
EPN2+=" --io-threads 4"
EPN2+=" --myId 2"
EPN2+=" --maxSlots 4"
EPN2+=" --numEPNS 3"
EPN2+=" --numFLPS 3"
EPN2+=" --mq-config $SchedulerFlpEpnconfig"
#EPN2+=" --channel-config name=epnsched,type=push,method=bind,rateLogging=0,address=tcp://localhost:5555"
#EPN2+=" --channel-config name=data1,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5556"
xterm -geometry 80x23+500+0 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$EPN2 &

EPN3="fairmq-ex-SCHEDULER-FLP-EPN-epn"
EPN3+=" --id epn3"
EPN3+=" --io-threads 4"
EPN3+=" --myId 3"
EPN3+=" --maxSlots 4"
EPN3+=" --numEPNS 3"
EPN3+=" --numFLPS 3"
EPN3+=" --mq-config $SchedulerFlpEpnconfig"
#EPN3+=" --channel-config name=epnsched,type=push,method=bind,rateLogging=0,address=tcp://localhost:5555"
#EPN3+=" --channel-config name=data1,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5556"
xterm -geometry 80x23+500+0 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$EPN3 &



SCHEDULER="fairmq-ex-SCHEDULER-FLP-EPN-scheduler"
SCHEDULER+=" --id scheduler1"
SCHEDULER+=" --io-threads 4"
SCHEDULER+=" --numEPNS 3"
SCHEDULER+=" --numFLPS 3"
SCHEDULER+=" --amountEPNs 3"
SCHEDULER+=" --mq-config $SchedulerFlpEpnconfig"
#SCHEDULER+=" --channel-config name=epnsched,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5555"
#SCHEDULER+=" --channel-config name=schedflp,type=push,method=bind,rateLogging=0,address=tcp://localhost:5557"
xterm -geometry 80x23+250+330 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$SCHEDULER &
