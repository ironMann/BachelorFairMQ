################################################################################
#    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
#                                                                              #
#              This software is distributed under the terms of the             #
#              GNU Lesser General Public Licence (LGPL) version 3,             #
#                  copied verbatim in the file "LICENSE"                       #
################################################################################

add_library(ExampleepntoschedulerLib STATIC
    "EPN.cxx"
    "EPN.h"
    "Scheduler.cxx"
    "Scheduler.h"
)

target_link_libraries(ExampleepntoschedulerLib PUBLIC FairMQ)

add_executable(fairmq-ex-epn-to-scheduler-EPN runEPN.cxx)
target_link_libraries(fairmq-ex-epn-to-scheduler-EPN PRIVATE ExampleepntoschedulerLib)

add_executable(fairmq-ex-epn-to-scheduler-scheduler runScheduler.cxx)
target_link_libraries(fairmq-ex-epn-to-scheduler-scheduler PRIVATE ExampleepntoschedulerLib)

add_custom_target(Exampleepntoscheduler DEPENDS fairmq-ex-epn-to-scheduler-EPN fairmq-ex-epn-to-scheduler-scheduler)

set(EX_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(FAIRMQ_BIN_DIR ${CMAKE_BINARY_DIR}/fairmq)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fairmq-start-ex-epn-to-scheduler.sh.in ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-epn-to-scheduler.sh)

# test

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test-ex-epn-to-scheduler.sh.in ${CMAKE_CURRENT_BINARY_DIR}/test-ex-epn-to-scheduler.sh)

add_test(NAME Example-epn-to-scheduler-zeromq COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test-ex-epn-to-scheduler.sh zeromq)
set_tests_properties(Example-epn-to-scheduler-zeromq PROPERTIES TIMEOUT "30" RUN_SERIAL true PASS_REGULAR_EXPRESSION "Received: ")

if(BUILD_NANOMSG_TRANSPORT)
  add_test(NAME Example-epn-to-scheduler-nanomsg COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test-ex-epn-to-scheduler.sh nanomsg)
  set_tests_properties(Example-epn-to-scheduler-nanomsg PROPERTIES TIMEOUT "30" RUN_SERIAL true PASS_REGULAR_EXPRESSION "Received: ")
endif()

add_test(NAME Example-epn-to-scheduler-shmem COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test-ex-epn-to-scheduler.sh shmem)
set_tests_properties(Example-epn-to-scheduler-shmem PROPERTIES TIMEOUT "30" RUN_SERIAL true PASS_REGULAR_EXPRESSION "Received: ")

# install

install(
    TARGETS
    fairmq-ex-epn-to-scheduler-EPN
    fairmq-ex-epn-to-scheduler-scheduler

    LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${PROJECT_INSTALL_BINDIR}
)

# configure run script with different executable paths for build and for install directories
set(EX_BIN_DIR ${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_BINDIR})
set(FAIRMQ_BIN_DIR ${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_BINDIR}/fairmq)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fairmq-start-ex-epn-to-scheduler.sh.in ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-epn-to-scheduler.sh_install)

install(
    PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-epn-to-scheduler.sh_install
    DESTINATION ${PROJECT_INSTALL_BINDIR}
    RENAME fairmq-start-ex-epn-to-scheduler.sh
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/ex-epn-to-scheduler.json
    DESTINATION ${PROJECT_INSTALL_DATADIR}
)
