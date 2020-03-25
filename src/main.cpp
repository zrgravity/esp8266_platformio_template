#include <Arduino.h>
#include <ESP8266WiFi.h>          //ESP8266 Core WiFi Library
#include <FS.h>
#include <DNSServer.h>            //Local DNS Server used for redirecting all requests to the configuration portal
#include <ESP8266WebServer.h>     //Local WebServer used to serve the configuration portal
#include <WifiManager.h>
#include "WifiManagerConfig.h"

void setup() {
    // Setup Serial
    Serial.begin(115200);
    Serial.println();
    WiFi.setSleepMode(WIFI_LIGHT_SLEEP);  
    
    // Load config
    loadSavedConfig();

    // Setup Wifi Manager and auto-connect
    setupWifiManager();

    // Save updated parameters
    if (shouldSaveConfig)
        saveConfig();

    Serial.print("Local IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    delay(10000);
}