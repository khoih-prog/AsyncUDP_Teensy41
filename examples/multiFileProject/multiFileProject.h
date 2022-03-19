/****************************************************************************************************************************
  multiFileProject.h
  For Teensy41 with QNEthernet
  
  AsyncUDP_Teensy41 is a Async UDP library for the Teensy41 using built-in Ethernet and QNEThernet
  
  Based on and modified from ESPAsyncUDP Library (https://github.com/me-no-dev/ESPAsyncUDP)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncUDP_Teensy41
*****************************************************************************************************************************/

// To demo how to include files in multi-file Projects

#pragma once

#define _TEENSY41_ASYNC_TCP_LOGLEVEL_       1

// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include <AsyncUDP_Teensy41.hpp>        // https://github.com/khoih-prog/AsyncUDP_Teensy41
