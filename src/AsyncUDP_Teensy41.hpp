/****************************************************************************************************************************
  AsyncUDP_Teensy41.hpp
  
  For Teensy41 with QNEthernet
  
  ASYNC_UDP_Teensy41 is a Async UDP library for the Teensy41 using built-in Ethernet and QNEThernet
  
  Based on and modified from ESPAsyncUDP Library (https://github.com/me-no-dev/ESPAsyncUDP)
  Built by Khoi Hoang https://github.com/khoih-prog/ASYNC_UDP_Teensy41
  
  Version: 1.2.1
  
  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.2.1   K Hoang      18/03/2022 Initial coding for Teensy 4.1 using built-in QNEthernet.
                                  Bump up version to v1.2.1 to sync with ASYNC_UDP_Teensy41 v1.2.1            
 *****************************************************************************************************************************/

#pragma once

#ifndef ASYNC_UDP_TEENSY41_HPP
#define ASYNC_UDP_TEENSY41_HPP

#include "Arduino.h"
#include "IPAddress.h"
#include "Print.h"
#include <functional>

#include "AsyncUDP_Teensy41_Debug.h"

#include "QNEthernet.h"       // https://github.com/ssilverman/QNEthernet
using namespace qindesign::network;

#if defined(__DOXYGEN__)
  #undef __DOXYGEN__
#endif

#define LWIP_IGMP         1
#define LWIP_IPV4         1

extern "C"
{
  #include "lwip/init.h"
  #include "lwip/opt.h"
  #include "lwip/ip_addr.h"
  #include "lwip/inet.h"
  #include "lwip/err.h"
  #include "lwip/pbuf.h"
  #include "lwip/udp.h"
  #include "lwip/igmp.h"
  #include "lwip/dns.h"
};

#ifndef TCP_MSS
  /* TCP Maximum segment size. */
  #define TCP_MSS                 (1500 - 40)   /* TCP_MSS = (Ethernet MTU - IP header size - TCP header size) = 1460 */
#endif

class AsyncUDP;
class AsyncUDPPacket;
class AsyncUDPMessage;

struct udp_pcb;
struct pbuf;

#if LWIP_VERSION_MAJOR == 1
  struct ip_addr;
  typedef struct ip_addr ip_addr_t;
#else
  struct ip4_addr;
  typedef struct ip4_addr ip_addr_t;
#endif

class AsyncUDPMessage : public Print
{
  protected:
    uint8_t *_buffer;
    size_t _index;
    size_t _size;

  public:
    AsyncUDPMessage(size_t size = TCP_MSS /*1460*/);
    virtual ~AsyncUDPMessage();

    size_t write(const uint8_t *data, size_t len);
    size_t write(uint8_t data);
    size_t space();
    uint8_t * data();
    size_t length();
    void flush();

    operator bool()
    {
      return _buffer != NULL;
    }
};

//////////////////////////////////

class AsyncUDPPacket : public Print
{
  protected:
    AsyncUDP *_udp;
    ip_addr_t *_localIp;
    uint16_t _localPort;
    ip_addr_t *_remoteIp;
    uint16_t _remotePort;
    uint8_t *_data;
    size_t _len;

  public:
    AsyncUDPPacket(AsyncUDP *udp, ip_addr_t *localIp, const uint16_t& localPort, ip_addr_t *remoteIp,
                   const uint16_t& remotePort, uint8_t *data, size_t len);
    virtual ~AsyncUDPPacket();

    uint8_t * data();
    size_t length();
    bool isBroadcast();
    bool isMulticast();

    IPAddress localIP();
    uint16_t localPort();
    IPAddress remoteIP();
    uint16_t remotePort();

    size_t send(AsyncUDPMessage &message);

    size_t write(const uint8_t *data, size_t len);
    size_t write(uint8_t data);
};

//////////////////////////////////

typedef std::function<void(AsyncUDPPacket& packet)> AuPacketHandlerFunction;
typedef std::function<void(void * arg, AsyncUDPPacket& packet)> AuPacketHandlerFunctionWithArg;

//////////////////////////////////

class AsyncUDP : public Print
{
  protected:
    udp_pcb *_pcb;
    bool _connected;
    AuPacketHandlerFunction _handler;

    void _recv(udp_pcb *upcb, pbuf *pb, ip_addr_t *addr, const uint16_t& port);
    
#if LWIP_VERSION_MAJOR == 1
    static void _s_recv(void *arg, udp_pcb *upcb, pbuf *p, ip_addr_t *addr, uint16_t port);
#else
    static void _s_recv(void *arg, udp_pcb *upcb, pbuf *p, const ip_addr_t *addr, uint16_t port);
#endif

  public:
    AsyncUDP();
    virtual ~AsyncUDP();

    void onPacket(AuPacketHandlerFunctionWithArg cb, void * arg = NULL);
    void onPacket(AuPacketHandlerFunction cb);

    bool listen(ip_addr_t *addr, const uint16_t& port);
    bool listen(const IPAddress addr, const uint16_t& port);
    bool listen(const uint16_t& port);

    bool listenMulticast(ip_addr_t *addr, const uint16_t& port, uint8_t ttl = 1);
    bool listenMulticast(const IPAddress addr, const uint16_t& port, uint8_t ttl = 1);

    bool connect(ip_addr_t *addr, const uint16_t& port);
    bool connect(const IPAddress addr, const uint16_t& port);

    void close();

    size_t writeTo(const uint8_t *data, size_t len, ip_addr_t *addr, const uint16_t& port);
    size_t writeTo(const uint8_t *data, size_t len, const IPAddress addr, const uint16_t& port);
    size_t write(const uint8_t *data, size_t len);
    size_t write(uint8_t data);

    size_t broadcastTo(uint8_t *data, size_t len, const uint16_t& port);
    size_t broadcastTo(const char * data, const uint16_t& port);
    size_t broadcast(uint8_t *data, size_t len);
    size_t broadcast(const char * data);

    size_t sendTo(AsyncUDPMessage &message, ip_addr_t *addr, const uint16_t& port);
    size_t sendTo(AsyncUDPMessage &message, const IPAddress addr, const uint16_t& port);
    size_t send(AsyncUDPMessage &message);

    size_t broadcastTo(AsyncUDPMessage &message, const uint16_t& port);
    size_t broadcast(AsyncUDPMessage &message);

    bool connected();
    operator bool();
};

#endif    //ASYNC_UDP_TEENSY41_HPP
