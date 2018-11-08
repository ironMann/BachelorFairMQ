# CMake generated Testfile for 
# Source directory: /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN
# Build directory: /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Example-SCHEDULER-FLP-EPN-zeromq "/home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/test-ex-SCHEDULER-FLP-EPN.sh" "zeromq")
set_tests_properties(Example-SCHEDULER-FLP-EPN-zeromq PROPERTIES  PASS_REGULAR_EXPRESSION "Received messages from both sources." RUN_SERIAL "true" TIMEOUT "30")
