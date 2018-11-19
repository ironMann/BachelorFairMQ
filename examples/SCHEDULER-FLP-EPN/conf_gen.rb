#!/usr/bin/env ruby


require 'pp'
require 'json'
require 'io/console'

def usage(fail)
  usage = %{
Usage:
  conf_gen.rb <num-FLP> <num-EPN> <node_list>

  NOTE: <node_list> must contain at least 3 nodes

  Examples:
  $ conf_gen.rb 20 10 pn02,pn04,pn05,pn06,pn07,pn08,pn10,pn11,pn12,pn13,pn15,pn16



  To expand the compressed node list format of slurm, e.g.:
  $ conf_gen.rb 20 10 $(scontrol show hostname pn[02,04-08,10-13,15-40] | paste -d, -s)
}
  puts usage
  exit 1 if fail
end


usage(true) if ARGV[0].nil? or ARGV[0].length==0 or ARGV[1].nil? or ARGV[2].nil?


NUM_FLP = ARGV[0].to_i
NUM_EPN = ARGV[1].to_i
NODES = ARGV[2].split(',')
NUM_NODES = NODES.length

usage(true) if NODES.length < 3 or NUM_FLP <= 0 or NUM_EPN <= 0


puts "Num of FLPs: " + NUM_FLP.to_s
puts "Num of EPNs: " + NUM_EPN.to_s
puts "Nodes: " + NODES.join(', ')

# 1st node is scheduler!
# the rest of the nodes are split between FLPs and EPNs

SCHED_NODE = NODES[0]
NUM_FLP_NODES = [NUM_FLP, ((NUM_FLP.to_f) / (NUM_FLP + NUM_EPN).to_f * (NUM_NODES - 1).to_f).to_i].min
NUM_EPN_NODES = [NUM_EPN, NUM_NODES - 1 - NUM_FLP_NODES].min

FLP_NODES = NODES[1...(1+NUM_FLP_NODES)]
EPN_NODES = NODES[(1+NUM_FLP_NODES)...(1+NUM_FLP_NODES+NUM_EPN_NODES)]

puts "Scheduler node: " + SCHED_NODE
puts "Num of FLP nodes: " + NUM_FLP_NODES.to_s + " : " + FLP_NODES.join(', ')
puts "Num of EPN nodes: " + NUM_EPN_NODES.to_s + " : " + EPN_NODES.join(', ')

SOCKET_HASH =
{
  :type => "pair", # "push"/"pull", "pair"
  :method => "", # "bind" or "connect"
  :address => "", #"tcp://localhost:5556",
  :sndBufSize => 1000,
  :rcvBufSize => 1000,
  :rateLogging => 10
}

CHAN_HASH =
{
  :name => "",
  :sockets => [ ]
}

DEVICE_HASH =
{
  :id => "",
  :channels => [ ]
}

###################
FLP_DATA_PORT = 20000
flp_port_per_node = {} # track used data ports on each flp node

flp_config = []
# create all flp devices
NUM_FLP.times do | flp |
  flp_node = FLP_NODES[flp % NUM_FLP_NODES]

  # init used port for this node
  flp_port_per_node[flp_node] = FLP_DATA_PORT if flp_port_per_node[flp_node].nil?

  flp_dev = Marshal.load(Marshal.dump(DEVICE_HASH))

  flp_dev[:id] = "flp#{flp}"

  # data channel for the current flp
  flp_data_chan = Marshal.load(Marshal.dump(CHAN_HASH))
  flp_data_chan[:name] = "data"
  # flp sockets all do bind
  NUM_EPN.times do | epn |
    epn_socket = Marshal.load(Marshal.dump(SOCKET_HASH))
    epn_socket[:type] = "push"
    epn_socket[:method] = "bind"
    epn_socket[:address] = "tcp://#{flp_node}:#{flp_port_per_node[flp_node]}"
    flp_port_per_node[flp_node] += 1

    flp_data_chan[:sockets] << epn_socket
  end

  flp_dev[:channels] << flp_data_chan

  flp_config << flp_dev
end




###################

epn_config = []
# create all flp devices
NUM_EPN.times do | epn |
  epn_node = EPN_NODES[epn % NUM_EPN_NODES]

  # init used port for this node
  # flp_port_per_node[flp_node] = FLP_DATA_PORT if flp_port_per_node[flp_node].nil?

  epn_dev = Marshal.load(Marshal.dump(DEVICE_HASH))

  epn_dev[:id] = "epn#{epn}"

  # data channel for the current flp
  epn_data_chan = Marshal.load(Marshal.dump(CHAN_HASH))
  epn_data_chan[:name] = "data"
  # flp sockets all do bind
  NUM_FLP.times do | flp |
    flp_socket = Marshal.load(Marshal.dump(SOCKET_HASH))
    flp_socket[:type] = "pull"
    flp_socket[:method] = "connect"
    flp_socket[:address] = flp_config[flp][:channels][0][:sockets][epn][:address]

    epn_data_chan[:sockets] << flp_socket
  end

  epn_dev[:channels] << epn_data_chan

  epn_config << epn_dev
end



FAIRMQ_DEVS =
{
  :fairMQOptions =>
  {
    :devices => [ flp_config, epn_config ].flatten
  }
}


# pp flp_config
# pp epn_config
puts "\n---------- ✂︎ CUT HERE ----------\n"

puts JSON.pretty_generate(FAIRMQ_DEVS)

puts "\n---------- ✂︎ CUT HERE ----------\n"
