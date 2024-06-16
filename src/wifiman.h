/*
#####################################################################################
# File: wifiman.h                                                                   #
# File Created: Friday, 19th April 2024 2:25:42 pm                                  #
# Author: Sergey Ko                                                                 #
# Last Modified: Thursday, 13th June 2024 4:40:11 pm                      #
# Modified By: Sergey Ko                                                            #
#####################################################################################
# CHANGELOG:                                                                        #
#####################################################################################
*/

#ifndef _WIFIMAN_H_
#define _WIFIMAN_H_

#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <ESP8266mDNS.h>
#include <ArduinoOTA.h>
#include "tv5725.h"
#include "options.h"
#include "wserial.h"

extern DNSServer dnsServer;

//  HOWTO: Rely on the previously implemented logic
//    __________     _____________     __________________  yes  _____________________
//   | if ssid | -> | connect AP | -> | connect failed? | ---> | fallback to APmode |
//   ----------     -------------     ------------------       ---------------------
//      ^                 _________________     |_____________
//      |                |      yes       v          no      |
//      | no  ____________________       _______________     |
//      ---- | is now connected? | < -- | continue ops | < --
//           --------------------       ---------------
//
//  THE OBJECTIVE: Do not rely on build-in autoreconnect routine,
//                 use the custom one instead.

// void updateWebSocketData();
void wifiInit();
void wifiDisable();
bool wifiStartStaMode(const String & ssid, const String & pass = "");
bool wifiStartApMode();
bool wifiStartWPS();
void wifiLoop();
const String wifiGetApSSID();
const String wifiGetApPASS();
int8_t wifiGetRSSI();
// void wifiReset();

#endif                                  // _WIFIMAN_H_