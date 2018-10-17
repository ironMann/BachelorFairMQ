# CMake generated Testfile for 
# Source directory: /home/charlotte/fairmq/examples/epn-to-scheduler
# Build directory: /home/charlotte/fairmq/examples/epn-to-scheduler
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Example-epn-to-scheduler-zeromq "/home/charlotte/fairmq/examples/epn-to-scheduler/test-ex-epn-to-scheduler.sh" "zeromq")
set_tests_properties(Example-epn-to-scheduler-zeromq PROPERTIES  PASS_REGULAR_EXPRESSION "Received: " RUN_SERIAL "true" TIMEOUT "30")
add_test(Example-epn-to-scheduler-shmem "/home/charlotte/fairmq/examples/epn-to-scheduler/test-ex-epn-to-scheduler.sh" "shmem")
set_tests_properties(Example-epn-to-scheduler-shmem PROPERTIES  PASS_REGULAR_EXPRESSION "Received: " RUN_SERIAL "true" TIMEOUT "30")
