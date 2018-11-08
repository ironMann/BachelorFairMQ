 ################################################################################
 #    Copyright (C) 2014 GSI Helmholtzzentrum fuer Schwerionenforschung GmbH    #
 #                                                                              #
 #              This software is distributed under the terms of the             #
 #              GNU Lesser General Public Licence (LGPL) version 3,             #
 #                  copied verbatim in the file "LICENSE"                       #
 ################################################################################

add_library(ExampleSCHEDULERFLPEPNLib STATIC
    "flp.cxx"
    "flp.h"
    "scheduler.cxx"
    "scheduler.h"
    "epn.cxx"
    "epn.h"
)

target_link_libraries(ExampleSCHEDULERFLPEPNLib PUBLIC FairMQ)

add_executable(fairmq-ex-SCHEDULER-FLP-EPN-flp runFlp.cxx)
target_link_libraries(fairmq-ex-SCHEDULER-FLP-EPN-flp PRIVATE ExampleSCHEDULERFLPEPNLib)

add_executable(fairmq-ex-SCHEDULER-FLP-EPN-scheduler runScheduler.cxx)
target_link_libraries(fairmq-ex-SCHEDULER-FLP-EPN-scheduler PRIVATE ExampleSCHEDULERFLPEPNLib)

add_executable(fairmq-ex-SCHEDULER-FLP-EPN-epn runEpn.cxx)
target_link_libraries(fairmq-ex-SCHEDULER-FLP-EPN-epn PRIVATE ExampleSCHEDULERFLPEPNLib)

add_custom_target(ExampleSCHEDULERFLPEPN DEPENDS fairmq-ex-SCHEDULER-FLP-EPN-flp fairmq-ex-SCHEDULER-FLP-EPN-scheduler fairmq-ex-SCHEDULER-FLP-EPN-epn)

set(EX_BIN_DIR ${CMAKE_CURRENT_BINARY_DIR})
set(FAIRMQ_BIN_DIR ${CMAKE_BINARY_DIR}/fairmq)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fairmq-start-ex-SCHEDULER-FLP-EPN.sh.in ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-SCHEDULER-FLP-EPN.sh)

# test

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/test-ex-SCHEDULER-FLP-EPN.sh.in ${CMAKE_CURRENT_BINARY_DIR}/test-ex-SCHEDULER-FLP-EPN.sh)

add_test(NAME Example-SCHEDULER-FLP-EPN-zeromq COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test-ex-SCHEDULER-FLP-EPN.sh zeromq)
set_tests_properties(Example-SCHEDULER-FLP-EPN-zeromq PROPERTIES TIMEOUT "30" RUN_SERIAL true PASS_REGULAR_EXPRESSION "Received messages from both sources.")

if(BUILD_NANOMSG_TRANSPORT)
  add_test(NAME Example-SCHEDULER-FLP-EPN-nanomsg COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test-ex-SCHEDULER-FLP-EPN.sh nanomsg)
  set_tests_properties(Example-SCHEDULER-FLP-EPN-nanomsg PROPERTIES TIMEOUT "30" RUN_SERIAL true PASS_REGULAR_EXPRESSION "Received messages from both sources.")
endif()

# install

install(
    TARGETS
    fairmq-ex-SCHEDULER-FLP-EPN-flp
    fairmq-ex-SCHEDULER-FLP-EPN-scheduler
    fairmq-ex-SCHEDULER-FLP-EPN-epn

    LIBRARY DESTINATION ${PROJECT_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${PROJECT_INSTALL_BINDIR}
)

# configure run script with different executable paths for build and for install directories
set(EX_BIN_DIR ${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_BINDIR})
set(FAIRMQ_BIN_DIR ${CMAKE_INSTALL_PREFIX}/${PROJECT_INSTALL_BINDIR}/fairmq)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/fairmq-start-ex-SCHEDULER-FLP-EPN.sh.in ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-SCHEDULER-FLP-EPN.sh_install)

install(
    PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/fairmq-start-ex-SCHEDULER-FLP-EPN.sh_install
    DESTINATION ${PROJECT_INSTALL_BINDIR}
    RENAME fairmq-start-ex-SCHEDULER-FLP-EPN.sh
)
