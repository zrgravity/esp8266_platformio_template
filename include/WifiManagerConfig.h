/*
    WifiManagerConfig.h
    Configuration save and load for WifiManager

    Edit the following:
        - Edit the ---- Configuration Variables ---- sections in this file
        - Edit the ---- Configuration Variables ---- sections in WifiManagerConfig.cpp
*/
#ifndef WIFIMANAGERCONFIG_H
#define WIFIMANAGERCONFIG_H

#include <WiFiManager.h>

// ---- Configuration Variables ----
extern char config_server[];
extern char config_port[];
extern char config_name[];
// ---- END Configuration Variables ----

extern bool shouldSaveConfig;

void saveConfigCallback();
void loadSavedConfig();
void saveConfig();
void setupWifiManager();

#endif