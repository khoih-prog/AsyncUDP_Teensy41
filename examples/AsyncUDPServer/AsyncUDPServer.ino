/****************************************************************************************************************************
  Async_UdpServer.ino

  For Teensy41 with QNEthernet
  
  AsyncUDP_Teensy41 is a Async UDP library for the Teensy41 using built-in Ethernet and QNEThernet
  
  Based on and modified from ESPAsyncUDP Library (https://github.com/me-no-dev/ESPAsyncUDP)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncUDP_Teensy41
 *****************************************************************************************************************************/

#include "defines.h"

#define ASYNC_UDP_TEENSY41_VERSION_MIN_TARGET      "AsyncUDP_Teensy41 v1.2.1"
#define ASYNC_UDP_TEENSY41_VERSION_MIN             1002001

#include <AsyncUDP_Teensy41.h>        // https://github.com/khoih-prog/AsyncUDP_Teensy41

#include <Ticker.h>                   // https://github.com/sstaub/Ticker

AsyncUDP udp;

// 600s = 10 minutes to not flooding, 60s in testing
#define UDP_REQUEST_INTERVAL_MS     60000  //600000

void sendRequest();

// Repeat forever, millis() resolution
Ticker sendUDPRequest(sendRequest, UDP_REQUEST_INTERVAL_MS, 0, MILLIS); 

void sendRequest()
{
  UDP_LOGDEBUG("Send broadcast");
  
  udp.broadcast("Anyone here?");
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  
  Serial.print("\nStart AsyncUDPServer on "); Serial.println(BOARD_NAME);
  Serial.println(ASYNC_UDP_TEENSY41_VERSION);

#if defined(ASYNC_UDP_TEENSY41_VERSION_MIN)
  if (ASYNC_UDP_TEENSY41_VERSION_INT < ASYNC_UDP_TEENSY41_VERSION_MIN)
  {
    Serial.print("Warning. Must use this example on Version equal or later than : ");
    Serial.println(ASYNC_UDP_TEENSY41_VERSION_MIN_TARGET);
  }
#endif  

  delay(500);

#if USING_DHCP
  // Start the Ethernet connection, using DHCP
  Serial.print("Initialize Ethernet using DHCP => ");
  Ethernet.begin();
#else
  // Start the Ethernet connection, using static IP
  Serial.print("Initialize Ethernet using static IP => ");
  Ethernet.begin(myIP, myNetmask, myGW);
  Ethernet.setDNSServerIP(mydnsServer);
#endif

  if (!Ethernet.waitForLocalIP(5000))
  {
    Serial.println(F("Failed to configure Ethernet"));

    if (!Ethernet.linkStatus())
    {
      Serial.println(F("Ethernet cable is not connected."));
    }

    // Stay here forever
    while (true)
    {
      delay(1);
    }
  }
  else
  {
    Serial.print(F("Connected! IP address:")); Serial.println(Ethernet.localIP());
  }

#if USING_DHCP
  delay(1000);
#else  
  delay(2000);
#endif
 
  if (udp.listen(1234)) 
  {
    Serial.print("UDP Listening on IP: ");
    Serial.println(Ethernet.localIP());
    
    udp.onPacket([](AsyncUDPPacket packet) 
    {
      Serial.print("UDP Packet Type: ");
      Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
      Serial.print(", From: ");
      Serial.print(packet.remoteIP());
      Serial.print(":");
      Serial.print(packet.remotePort());
      Serial.print(", To: ");
      Serial.print(packet.localIP());
      Serial.print(":");
      Serial.print(packet.localPort());
      Serial.print(", Length: ");
      Serial.print(packet.length());
      Serial.print(", Data: ");
      Serial.write(packet.data(), packet.length());
      Serial.println();
      //reply to the client
      packet.printf("Got %u bytes of data", packet.length());
    });
  }

   sendRequest();

  sendUDPRequest.start(); //start the ticker
}

void loop()
{
  sendUDPRequest.update();
}
