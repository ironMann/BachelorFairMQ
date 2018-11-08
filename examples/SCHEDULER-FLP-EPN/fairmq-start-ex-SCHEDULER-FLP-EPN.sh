#!/bin/bash

export FAIRMQ_PATH=/home/charlotte/fairmq/fairmq

FLP="fairmq-ex-SCHEDULER-FLP-EPN-flp"
FLP+=" --id flp1"
FLP+=" --rate 4"
FLP+=" --channel-config name=schedflp,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5557"
FLP+="                  name=data1,type=push,method=bind,rateLogging=0,address=tcp://localhost:5556"
xterm -geometry 80x23+0+0 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$FLP &

EPN="fairmq-ex-SCHEDULER-FLP-EPN-epn"
EPN+=" --id epn1"
EPN+=" --rate 4"
EPN+=" --myId 1"
EPN+=" --maxSlots 4"
EPN+=" --numEPNS 1"
EPN+=" --numFLPS 1"
EPN+=" --channelname 1"
EPN+=" --channel-config name=epnsched,type=push,method=bind,rateLogging=0,address=tcp://localhost:5555"
EPN+=" --channel-config name=data1,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5556"
xterm -geometry 80x23+500+0 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$EPN &

SCHEDULER="fairmq-ex-SCHEDULER-FLP-EPN-scheduler"
SCHEDULER+=" --id scheduler1"
SCHEDULER+=" --rate 4"
SCHEDULER+=" --numEPNS 1"
SCHEDULER+=" --numFLPS 1"
SCHEDULER+=" --channel-config name=epnsched,type=pull,method=connect,rateLogging=0,address=tcp://localhost:5555"
SCHEDULER+=" --channel-config name=schedflp,type=push,method=bind,rateLogging=0,address=tcp://localhost:5557"

xterm -geometry 80x23+250+330 -hold -e /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/$SCHEDULER &
