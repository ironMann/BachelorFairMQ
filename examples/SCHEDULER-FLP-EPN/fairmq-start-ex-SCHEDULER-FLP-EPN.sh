#!/bin/bash

export FAIRMQ_PATH=/home/charlotte/fairmq/fairmq

SchedulerFlpEpnconfig="/home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/ex-SCHEDULER-FLP-EPN.json"

FLP="fairmq-ex-SCHEDULER-FLP-EPN-flp"
FLP+=" --id flp1"
FLP+=" --rate 4"
FLP+=" --amountEPNs 3"
FLP+=" --mq-config $SchedulerFlpEpnconfig"
#FLP+=" --channel-config name=schedflp,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5557"
#FLP+="                  name=data1,type=push,method=bind,rateLogging=0,address=tcp://localhost:5556"
xterm -geometry 80x23+0+0 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$FLP &

EPN1="fairmq-ex-SCHEDULER-FLP-EPN-epn"
EPN1+=" --id epn1"
EPN1+=" --rate 4"
EPN1+=" --myId 1"
EPN1+=" --maxSlots 4"
EPN1+=" --numEPNS 3"
EPN1+=" --numFLPS 1"
EPN1+=" --channelname 1"
EPN1+=" --mq-config $SchedulerFlpEpnconfig"
#EPN1+=" --channel-config name=epnsched,type=push,method=bind,rateLogging=0,address=tcp://localhost:5555"
#EPN1+=" --channel-config name=data1,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5556"
xterm -geometry 80x23+500+0 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$EPN1 &

EPN2="fairmq-ex-SCHEDULER-FLP-EPN-epn"
EPN2+=" --id epn2"
EPN2+=" --rate 4"
EPN2+=" --myId 2"
EPN2+=" --maxSlots 4"
EPN2+=" --numEPNS 3"
EPN2+=" --numFLPS 1"
EPN2+=" --channelname 2"
EPN2+=" --mq-config $SchedulerFlpEpnconfig"
#EPN2+=" --channel-config name=epnsched,type=push,method=bind,rateLogging=0,address=tcp://localhost:5555"
#EPN2+=" --channel-config name=data1,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5556"
xterm -geometry 80x23+500+0 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$EPN2 &

EPN3="fairmq-ex-SCHEDULER-FLP-EPN-epn"
EPN3+=" --id epn3"
EPN3+=" --rate 4"
EPN3+=" --myId 3"
EPN3+=" --maxSlots 4"
EPN3+=" --numEPNS 3"
EPN3+=" --numFLPS 1"
EPN3+=" --channelname 3"
EPN3+=" --mq-config $SchedulerFlpEpnconfig"
#EPN3+=" --channel-config name=epnsched,type=push,method=bind,rateLogging=0,address=tcp://localhost:5555"
#EPN3+=" --channel-config name=data1,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5556"
xterm -geometry 80x23+500+0 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$EPN3 &



SCHEDULER="fairmq-ex-SCHEDULER-FLP-EPN-scheduler"
SCHEDULER+=" --id scheduler1"
SCHEDULER+=" --rate 4"
SCHEDULER+=" --numEPNS 3"
SCHEDULER+=" --numFLPS 1"
SCHEDULER+=" --amountEPNs 3"
SCHEDULER+=" --mq-config $SchedulerFlpEpnconfig"
#SCHEDULER+=" --channel-config name=epnsched,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5555"
#SCHEDULER+=" --channel-config name=schedflp,type=push,method=bind,rateLogging=0,address=tcp://localhost:5557"
xterm -geometry 80x23+250+330 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$SCHEDULER &
