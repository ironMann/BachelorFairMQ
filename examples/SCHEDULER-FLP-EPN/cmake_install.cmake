# Install script for directory: /home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/home/charlotte/fairmq/fairmq_install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "RelWithDebInfo")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-flp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-flp")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-flp"
         RPATH "$ORIGIN/../lib:/usr/local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/fairmq-ex-SCHEDULER-FLP-EPN-flp")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-flp" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-flp")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-flp"
         OLD_RPATH "/home/charlotte/fairmq/boost/stage/lib:/home/charlotte/fairmq/fairmq:/home/charlotte/fairmq/FairLogger_build/FairLogger_install/lib:/usr/local/lib:"
         NEW_RPATH "$ORIGIN/../lib:/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-flp")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-scheduler" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-scheduler")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-scheduler"
         RPATH "$ORIGIN/../lib:/usr/local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/fairmq-ex-SCHEDULER-FLP-EPN-scheduler")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-scheduler" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-scheduler")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-scheduler"
         OLD_RPATH "/home/charlotte/fairmq/boost/stage/lib:/home/charlotte/fairmq/fairmq:/home/charlotte/fairmq/FairLogger_build/FairLogger_install/lib:/usr/local/lib:"
         NEW_RPATH "$ORIGIN/../lib:/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-scheduler")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-epn" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-epn")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-epn"
         RPATH "$ORIGIN/../lib:/usr/local/lib")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "/home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/fairmq-ex-SCHEDULER-FLP-EPN-epn")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-epn" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-epn")
    file(RPATH_CHANGE
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-epn"
         OLD_RPATH "/home/charlotte/fairmq/boost/stage/lib:/home/charlotte/fairmq/fairmq:/home/charlotte/fairmq/FairLogger_build/FairLogger_install/lib:/usr/local/lib:"
         NEW_RPATH "$ORIGIN/../lib:/usr/local/lib")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/fairmq-ex-SCHEDULER-FLP-EPN-epn")
    endif()
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE PROGRAM RENAME "fairmq-start-ex-SCHEDULER-FLP-EPN.sh" FILES "/home/charlotte/fairmq/examples/SCHEDULER-FLP-EPN/fairmq-start-ex-SCHEDULER-FLP-EPN.sh_install")
endif()

