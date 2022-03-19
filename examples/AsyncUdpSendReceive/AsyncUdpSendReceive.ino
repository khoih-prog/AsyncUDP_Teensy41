/****************************************************************************************************************************
  AsyncUDPSendReceive.ino

  For Teensy41 with QNEthernet
  
  AsyncUDP_Teensy41 is a Async UDP library for the Teensy41 using built-in Ethernet and QNEThernet
  
  Based on and modified from ESPAsyncUDP Library (https://github.com/me-no-dev/ESPAsyncUDP)
  Built by Khoi Hoang https://github.com/khoih-prog/AsyncUDP_Teensy41
 *****************************************************************************************************************************/

#include "defines.h"
#include <time.h>

#include <Ticker.h>                   // https://github.com/sstaub/Ticker

//IPAddress timeServerIP = IPAddress(13, 86, 101, 172);     // timeWindowsCom
IPAddress timeServerIP = IPAddress(208, 81, 1, 244);

#define NTP_REQUEST_PORT      123

char ReplyBuffer[] = "ACK";      // a string to send back

char timeServer[]         = "time.nist.gov";  // NTP server

const int NTP_PACKET_SIZE = 48;       // NTP timestamp is in the first 48 bytes of the message

byte packetBuffer[NTP_PACKET_SIZE];   // buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
AsyncUDP Udp;

// 600s = 10 minutes to not flooding, 60s in testing
#define UDP_REQUEST_INTERVAL_MS     60000  //600000

void sendNTPPacket();

// Repeat forever, millis() resolution
Ticker sendUDPRequest(sendNTPPacket, UDP_REQUEST_INTERVAL_MS, 0, MILLIS); 


void sendACKPacket()
{
  Serial.println("============= sendACKPacket =============");
  
  // Send unicast ACK to the same remoteIP and remotePort we received the packet
  // The AsyncUDP_STM32 library will take care of the correct IP and port based on pcb
  Udp.write((uint8_t *) ReplyBuffer, sizeof(ReplyBuffer));
}

// send an NTP request to the time server at the given address
void createNTPpacket()
{
  Serial.println("============= createNTPpacket =============");

  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)

  packetBuffer[0]   = 0b11100011;   // LI, Version, Mode
  packetBuffer[1]   = 0;     // Stratum, or type of clock
  packetBuffer[2]   = 6;     // Polling Interval
  packetBuffer[3]   = 0xEC;  // Peer Clock Precision
  
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
}

void sendNTPPacket()
{
  createNTPpacket();
  //Send unicast
  Udp.write(packetBuffer, sizeof(packetBuffer));
}

void parsePacket(AsyncUDPPacket packet)
{
  struct tm  ts;
  char       buf[80];
  
  memcpy(packetBuffer, packet.data(), sizeof(packetBuffer));

  Serial.print("Received UDP Packet Type: ");
  Serial.println(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
  Serial.print("From: ");
  Serial.print(packet.remoteIP());
  Serial.print(":");
  Serial.print(packet.remotePort());
  Serial.print(", To: ");
  Serial.print(packet.localIP());
  Serial.print(":");
  Serial.print(packet.localPort());
  Serial.print(", Length: ");
  Serial.print(packet.length());
  Serial.println();

  unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
  unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);

  // combine the four bytes (two words) into a long integer
  // this is NTP time (seconds since Jan 1 1900):
  unsigned long secsSince1900 = highWord << 16 | lowWord;
  
  Serial.print(F("Seconds since Jan 1 1900 = "));
  Serial.println(secsSince1900);

  // now convert NTP time into )everyday time:
  Serial.print(F("Epoch/Unix time = "));
  
  // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
  const unsigned long seventyYears = 2208988800UL;
  
  // subtract seventy years:
  unsigned long epoch = secsSince1900 - seventyYears;
  time_t epoch_t = epoch;   //secsSince1900 - seventyYears;
 
  // print Unix time:
  Serial.println(epoch);

  // print the hour, minute and second:
  Serial.print(F("The UTC/GMT time is "));       // UTC is the time at Greenwich Meridian (GMT)

  ts = *localtime(&epoch_t);
  strftime(buf, sizeof(buf), "%a %Y-%m-%d %H:%M:%S %Z", &ts);
  Serial.println(buf);

  // send a reply, to the IP address and port that sent us the packet we received
  sendACKPacket();
}

void setup()
{
  Serial.begin(115200);
  while (!Serial);

  Serial.print("\nStart AsyncUDPSendReceive on "); Serial.println(BOARD_NAME);
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

  Serial.println(F("\nStarting connection to server..."));

  //NTP requests are to port NTP_REQUEST_PORT = 123
  if (Udp.connect(timeServerIP, NTP_REQUEST_PORT))
  {
    Serial.println("UDP connected");

    Udp.onPacket([](AsyncUDPPacket packet)
    {
      parsePacket(packet);
    });
  }

  sendNTPPacket();

  sendUDPRequest.start(); //start the ticker
}

void loop()
{
  sendUDPRequest.update();
}
