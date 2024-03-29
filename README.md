# AsyncUDP_Teensy41 Library


[![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncUDP_Teensy41.svg?)](https://www.ardu-badge.com/AsyncUDP_Teensy41)
[![GitHub release](https://img.shields.io/github/release/khoih-prog/AsyncUDP_Teensy41.svg)](https://github.com/khoih-prog/AsyncUDP_Teensy41/releases)
[![contributions welcome](https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat)](#Contributing)
[![GitHub issues](https://img.shields.io/github/issues/khoih-prog/AsyncUDP_Teensy41.svg)](http://github.com/khoih-prog/AsyncUDP_Teensy41/issues)


<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://cdn.buymeacoffee.com/buttons/v2/default-yellow.png" alt="Donate to my libraries using BuyMeACoffee" style="height: 50px !important;width: 181px !important;" ></a>
<a href="https://www.buymeacoffee.com/khoihprog6" title="Donate to my libraries using BuyMeACoffee"><img src="https://img.shields.io/badge/buy%20me%20a%20coffee-donate-orange.svg?logo=buy-me-a-coffee&logoColor=FFDD00" style="height: 20px !important;width: 200px !important;" ></a>

---
---

## Table of Contents


* [Why do we need this AsyncUDP_Teensy41 library](#why-do-we-need-this-AsyncUDP_Teensy41-library)
  * [Features](#features)
  * [Why Async is better](#why-async-is-better)
  * [Currently supported Boards](#currently-supported-boards)
* [Changelog](changelog.md)
* [Prerequisites](#prerequisites)
* [Installation](#installation)
  * [Use Arduino Library Manager](#use-arduino-library-manager)
  * [Manual Install](#manual-install)
  * [VS Code & PlatformIO](#vs-code--platformio)
* [Packages' Patches](#packages-patches)
  * [1. For Teensy boards](#1-for-teensy-boards)
* [HOWTO Fix `Multiple Definitions` Linker Error](#howto-fix-multiple-definitions-linker-error)
* [HOWTO Setting up the Async UDP Client](#howto-setting-up-the-async-udp-client)
* [Examples](#examples)
  * [ 1. AsyncUDPClient](examples/AsyncUDPClient)
  * [ 2. AsyncUDPMulticastServer](examples/AsyncUDPMulticastServer)
  * [ 3. AsyncUdpNTPClient](examples/AsyncUdpNTPClient)
  * [ 4. AsyncUdpSendReceive](examples/AsyncUdpSendReceive)
  * [ 5. AsyncUDPServer](examples/AsyncUDPServer) 
  * [ 6. multiFileProject](examples/multiFileProject)
* [Example AsyncUdpNTPClient](#example-asyncudpntpclient)
  * [1. File AsyncUdpNTPClient.ino](#1-file-asyncudpntpclientino)
  * [2. File defines.h](#2-file-definesh) 
* [Debug Terminal Output Samples](#debug-terminal-output-samples)
  * [1. AsyncUdpNTPClient on TEENSY 4.1](#1-AsyncUdpNTPClient-on-TEENSY-41)
  * [2. AsyncUDPSendReceive on TEENSY 4.1](#2-AsyncUDPSendReceive-on-TEENSY-41)
* [Debug](#debug)
* [Troubleshooting](#troubleshooting)
* [Issues](#issues)
* [TO DO](#to-do)
* [DONE](#done)
* [Contributions and Thanks](#contributions-and-thanks)
* [Contributing](#contributing)
* [License](#license)
* [Copyright](#copyright)

---
---

### Why do we need this [AsyncUDP_Teensy41 library](https://github.com/khoih-prog/AsyncUDP_Teensy41)

#### Features

This [AsyncUDP_Teensy41 library](https://github.com/khoih-prog/AsyncUDP_Teensy41) is a fully asynchronous UDP library, designed for a trouble-free, multi-connection network environment, for Teensy 4.1 using QNEthernet Library. The library is easy to use and includes support for Unicast, Broadcast and Multicast environments.

This library is based on, modified from:

1. [Hristo Gochkov's ESPAsyncUDP](https://github.com/me-no-dev/ESPAsyncUDP)

to apply the better and faster **asynchronous** feature of the **powerful** [ESPAsyncUDP Library](https://github.com/me-no-dev/ESPAsyncUDP) into Teensy 4.1 using QNEthernet Library.


#### Why Async is better

- Using asynchronous network means that you can handle **more than one connection at the same time**
- You are called once the request is ready and parsed
- When you send the response, you are **immediately ready** to handle other connections while the server is taking care of sending the response in the background
- **Speed is OMG**
- After connecting to a UDP server as an Async Client, you are **immediately ready** to handle other connections while the Client is taking care of receiving the UDP responding packets in the background.
- You are not required to check in a tight loop() the arrival of the UDP responding packets to process them.


### Currently Supported Boards

1. **Teensy 4.1 using QNEthernet Library**

---
---

## Prerequisites

 1. [`Arduino IDE 1.8.19+` for Arduino](https://github.com/arduino/Arduino). [![GitHub release](https://img.shields.io/github/release/arduino/Arduino.svg)](https://github.com/arduino/Arduino/releases/latest)
 2. [`Teensy core v1.57+`](https://www.pjrc.com/teensy/td_download.html) for Teensy 4.1
 3. [`QNEthernet Library version v0.16.0+`](https://github.com/ssilverman/QNEthernet) for Teensy 4.1 built-in Ethernet.
 
---

### Installation

The suggested way to install is to:

#### Use Arduino Library Manager

The best way is to use `Arduino Library Manager`. Search for `AsyncUDP_Teensy41`, then select / install the latest version. You can also use this link [![arduino-library-badge](https://www.ardu-badge.com/badge/AsyncUDP_Teensy41.svg?)](https://www.ardu-badge.com/AsyncUDP_Teensy41) for more detailed instructions.

### Manual Install

1. Navigate to [AsyncUDP_Teensy41](https://github.com/khoih-prog/AsyncUDP_Teensy41) page.
2. Download the latest release `AsyncUDP_Teensy41-main.zip`.
3. Extract the zip file to `AsyncUDP_Teensy41-main` directory 
4. Copy the whole `AsyncUDP_Teensy41-main` folder to Arduino libraries' directory such as `~/Arduino/libraries/`.

### VS Code & PlatformIO:

1. Install [VS Code](https://code.visualstudio.com/)
2. Install [PlatformIO](https://platformio.org/platformio-ide)
3. Install [**AsyncUDP_Teensy41** library](https://registry.platformio.org/libraries/khoih-prog/AsyncUDP_Teensy41) by using [Library Manager](https://registry.platformio.org/libraries/khoih-prog/AsyncUDP_Teensy41/installation). Search for AsyncUDP_Teensy41 in [Platform.io Author's Libraries](https://platformio.org/lib/search?query=author:%22Khoi%20Hoang%22)
4. Use included [platformio.ini](platformio/platformio.ini) file from examples to ensure that all dependent libraries will installed automatically. Please visit documentation for the other options and examples at [Project Configuration File](https://docs.platformio.org/page/projectconf.html)

---
---

### Packages' Patches

#### 1. For Teensy boards
 
 **To be able to compile and run on Teensy boards**, you have to copy the files in [**Packages_Patches for Teensy directory**](Packages_Patches/hardware/teensy/avr) into Teensy hardware directory (./arduino-1.8.19/hardware/teensy/avr/boards.txt). 

Supposing the Arduino version is 1.8.19. These files must be copied into the directory:

- `./arduino-1.8.19/hardware/teensy/avr/boards.txt`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-1.8.19/hardware/teensy/avr/cores/teensy4/Stream.h`

Whenever a new version is installed, remember to copy this file into the new version directory. For example, new version is x.yy.zz
These files must be copied into the directory:

- `./arduino-x.yy.zz/hardware/teensy/avr/boards.txt`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy3/Stream.h`
- `./arduino-x.yy.zz/hardware/teensy/avr/cores/teensy4/Stream.h`

---
---

### HOWTO Fix `Multiple Definitions` Linker Error

The current library implementation, using `xyz-Impl.h` instead of standard `xyz.cpp`, possibly creates certain `Multiple Definitions` Linker error in certain use cases.

You can include this `.hpp` file

```cpp
// Can be included as many times as necessary, without `Multiple Definitions` Linker Error
#include "AsyncUDP_Teensy41.hpp"         //https://github.com/khoih-prog/AsyncUDP_Teensy41
```

in many files. But be sure to use the following `.h` file **in just 1 `.h`, `.cpp` or `.ino` file**, which must **not be included in any other file**, to avoid `Multiple Definitions` Linker Error

```cpp
// To be included only in main(), .ino with setup() to avoid `Multiple Definitions` Linker Error
#include "AsyncUDP_Teensy41.h"           //https://github.com/khoih-prog/AsyncUDP_Teensy41
```

Check the new [**multiFileProject** example](examples/multiFileProject) for a `HOWTO` demo.

Have a look at the discussion in [Different behaviour using the src_cpp or src_h lib #80](https://github.com/khoih-prog/ESPAsync_WiFiManager/discussions/80)


---
---


## HOWTO Setting up the Async UDP Client

```cpp

#include <AsyncUDP_Teensy41.h>

IPAddress timeWindowsCom = IPAddress(13, 86, 101, 172);

#define NTP_REQUEST_PORT      123

const int NTP_PACKET_SIZE = 48;       // NTP timestamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE];   // buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
AsyncUDP Udp;

// send an NTP request to the time server at the given address
void createNTPpacket(void)
{
  ...
}

void sendNTPPacket(void)
{
  createNTPpacket();
  //Send unicast
  Udp.write(packetBuffer, sizeof(packetBuffer));
}

void parsePacket(AsyncUDPPacket packet)
{
  ...
}

void setup()
{
  ...
  
  //NTP requests are to port NTP_REQUEST_PORT = 123
  if (Udp.connect(timeWindowsCom, NTP_REQUEST_PORT))
  {
    // Setting up Async packet Handler
    Udp.onPacket([](AsyncUDPPacket packet)
    {
      parsePacket(packet);
    });
  }
}

void loop()
{
  sendNTPPacket();

  // wait 60 seconds before asking for the time again
  delay(60000);
}
```

---
---

### Examples

 1. [AsyncUDPClient](examples/AsyncUDPClient)
 2. [AsyncUDPMulticastServer](examples/AsyncUDPMulticastServer)
 3. [AsyncUdpNTPClient](examples/AsyncUdpNTPClient)
 4. [AsyncUdpSendReceive](examples/AsyncUdpSendReceive) 
 5. [AsyncUDPServer](examples/AsyncUDPServer)
 6. [multiFileProject](examples/multiFileProject)

---

### Example [AsyncUdpNTPClient](examples/AsyncUdpNTPClient)

#### 1. File [AsyncUdpNTPClient.ino](examples/AsyncUdpNTPClient/AsyncUdpNTPClient.ino)

https://github.com/khoih-prog/AsyncUDP_Teensy41/blob/f775e6189ef9dfd4b1f0cf9ad27eac60f0b6cba4/examples/AsyncUdpNTPClient/AsyncUdpNTPClient.ino#L12-L204


#### 2. File [defines.h](examples/AsyncUdpNTPClient/defines.h)

https://github.com/khoih-prog/AsyncUDP_Teensy41/blob/f775e6189ef9dfd4b1f0cf9ad27eac60f0b6cba4/examples/AsyncUdpNTPClient/defines.h#L12-L47

---

### Debug Terminal Output Samples

#### 1. AsyncUdpNTPClient on TEENSY 4.1

This is terminal debug output when running [AsyncUdpNTPClient](examples/AsyncUdpNTPClient) on  **Teensy 4.1 using built-in QNEthernet**. It connects to NTP Server "0.ca.pool.ntp.org" (IPAddress(208, 81, 1, 244)) using AsyncUDP_Teensy41 library, and requests NTP time every 60s. The packet is then **received and processed asynchronously** to print current UTC/GMT time.

```cpp
Start AsyncUdpNTPClient on TEENSY 4.1
AsyncUDP_Teensy41 v1.2.1
Initialize Ethernet using DHCP => Connected! IP address:192.168.2.107
UDP connected
============= createNTPpacket =============
[UDP] _recv: Call packetHandler with packet from remoteIP = 208.81.1.244 , remotePort = 123
[UDP] To destIP = 192.168.2.107 , destPort = 62927
[UDP] Packet len = 48
Received UDP Packet Type: Unicast
From: 208.81.1.244:123, To: 192.168.2.107:62927, Length: 48
Seconds since Jan 1 1900 = 3856651358
Epoch/Unix time = 1647662558
The UTC/GMT time is Sat 2022-03-19 04:02:38 GMT
============= createNTPpacket =============
[UDP] _recv: Call packetHandler with packet from remoteIP = 208.81.1.244 , remotePort = 123
[UDP] To destIP = 192.168.2.107 , destPort = 62927
[UDP] Packet len = 48
Received UDP Packet Type: Unicast
From: 208.81.1.244:123, To: 192.168.2.107:62927, Length: 48
Seconds since Jan 1 1900 = 3856651418
Epoch/Unix time = 1647662618
The UTC/GMT time is Sat 2022-03-19 04:03:38 GMT
============= createNTPpacket =============
[UDP] _recv: Call packetHandler with packet from remoteIP = 208.81.1.244 , remotePort = 123
[UDP] To destIP = 192.168.2.107 , destPort = 62927
[UDP] Packet len = 48
Received UDP Packet Type: Unicast
From: 208.81.1.244:123, To: 192.168.2.107:62927, Length: 48
Seconds since Jan 1 1900 = 3856651478
Epoch/Unix time = 1647662678
The UTC/GMT time is Sat 2022-03-19 04:04:38 GMT
```


---

#### 2. AsyncUDPSendReceive on TEENSY 4.1

This is terminal debug output when running [AsyncUDPSendReceive](examples/AsyncUDPSendReceive) on **Teensy 4.1 using built-in QNEthernet**. It connects to NTP Server "time.nist.gov" (IPAddress(208, 81, 1, 244)) using AsyncUDP_Teensy41 library, and requests NTP time every 60s. The packet is then **received and processed asynchronously** to print current UTC/GMT time.

```cpp
Start AsyncUDPSendReceive on TEENSY 4.1
AsyncUDP_Teensy41 v1.2.1
Initialize Ethernet using DHCP => Connected! IP address:192.168.2.107

Starting connection to server...
UDP connected
============= createNTPpacket =============
[UDP] _recv: Call packetHandler with packet from remoteIP = 208.81.1.244 , remotePort = 123
[UDP] To destIP = 192.168.2.107 , destPort = 62927
[UDP] Packet len = 48
Received UDP Packet Type: Unicast
From: 208.81.1.244:123, To: 192.168.2.107:62927, Length: 48
Seconds since Jan 1 1900 = 3856651920
Epoch/Unix time = 1647663120
The UTC/GMT time is Sat 2022-03-19 04:12:00 GMT
============= sendACKPacket =============
============= createNTPpacket =============
[UDP] _recv: Call packetHandler with packet from remoteIP = 208.81.1.244 , remotePort = 123
[UDP] To destIP = 192.168.2.107 , destPort = 62927
[UDP] Packet len = 48
Received UDP Packet Type: Unicast
From: 208.81.1.244:123, To: 192.168.2.107:62927, Length: 48
Seconds since Jan 1 1900 = 3856651980
Epoch/Unix time = 1647663180
The UTC/GMT time is Sat 2022-03-19 04:13:00 GMT
============= sendACKPacket =============
============= createNTPpacket =============
[UDP] _recv: Call packetHandler with packet from remoteIP = 208.81.1.244 , remotePort = 123
[UDP] To destIP = 192.168.2.107 , destPort = 62927
[UDP] Packet len = 48
Received UDP Packet Type: Unicast
From: 208.81.1.244:123, To: 192.168.2.107:62927, Length: 48
Seconds since Jan 1 1900 = 3856652040
Epoch/Unix time = 1647663240
The UTC/GMT time is Sat 2022-03-19 04:14:00 GMT
============= sendACKPacket =============
```

---
---

### Debug

Debug is enabled by default on Serial. To disable, use level 0

```cpp
#define ASYNC_UDP_TEENSY41_DEBUG_PORT      Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_UDP_TEENSY41_LOGLEVEL_      0
```

You can also change the debugging level from 0 to 4

```cpp
#define ASYNC_UDP_TEENSY41_DEBUG_PORT      Serial

// Use from 0 to 4. Higher number, more debugging messages and memory usage.
#define _ASYNC_UDP_TEENSY41_LOGLEVEL_      4
```

---

### Troubleshooting

If you get compilation errors, more often than not, you may need to install a newer version of Arduino IDE, the Arduino `STM32` core or depending libraries.

Sometimes, the library will only work if you update the `STM32` core to the latest version because I am always using the latest cores /libraries.

---
---


### Issues ###

Submit issues to: [AsyncUDP_Teensy41 issues](https://github.com/khoih-prog/AsyncUDP_Teensy41/issues)

---

## TO DO

 1. Fix bug. Add enhancement


## DONE

 1. Initial porting and coding for **Teensy 4.1 using built-in QNEthernet**
 2. Add more examples.
 3. Add debugging features.
 4. Add astyle using `allman` style. Restyle the library


---
---

### Contributions and Thanks

1. Based on and modified from [Hristo Gochkov's ESPAsyncUDP](https://github.com/me-no-dev/ESPAsyncUDP). Many thanks to [Hristo Gochkov](https://github.com/me-no-dev) for good [ESPAsyncUDP Library](https://github.com/me-no-dev/ESPAsyncUDP)


<table>
  <tr>
    <td align="center"><a href="https://github.com/me-no-dev"><img src="https://github.com/me-no-dev.png" width="100px;" alt="me-no-dev"/><br /><sub><b>⭐️⭐️ Hristo Gochkov</b></sub></a><br /></td>
  </tr> 
</table>

---

### Contributing

If you want to contribute to this project:

- Report bugs and errors
- Ask for enhancements
- Create issues and pull requests
- Tell other people about this library

---

### License

- The library is licensed under [GPLv3](https://github.com/khoih-prog/WebSockets2_Generic/blob/main/LICENSE)

---

## Copyright

- Copyright (c) 2016- Hristo Gochkov
- Copyright (c) 2022- Khoi Hoang


