/*
    WifiManagerConfig.cpp
    Configuration save and load for WifiManager

    Edit the following:
        - Edit the ---- Configuration Variables ---- sections in this file
        - Edit the ---- Configuration Variables ---- sections in WifiManagerConfig.h
    
*/
#include "WifiManagerConfig.h"
#include <ArduinoJson.h>

char config_server[40] = "server FQDN or IP";
char config_port[6] = "port#";
char config_name[40] = "Device name/etc";

bool shouldSaveConfig = false;

// Callback if config needs to be saved
void saveConfigCallback() {
    Serial.println("Should save config = true");
    shouldSaveConfig = true;
}

void loadSavedConfig() {
    //read configuration from FS json
    Serial.println("mounting FS...");

    if (SPIFFS.begin()) {
        Serial.println("mounted file system");
        if (SPIFFS.exists("/config.json")) {
            //file exists, reading and loading
            Serial.println("reading config file");
            File configFile = SPIFFS.open("/config.json", "r");
            if (configFile) {
            Serial.println("opened config file");
            size_t size = configFile.size();
            // Allocate a buffer to store contents of the file.
            std::unique_ptr<char[]> buf(new char[size]);

            configFile.readBytes(buf.get(), size);
            DynamicJsonDocument jsonDoc(1024);
            auto error = deserializeJson(jsonDoc, buf.get());
            serializeJson(jsonDoc, Serial);
            if (error) {
                Serial.print("failed to load json config. deserializeJson() failed with code: ");
                Serial.println(error.c_str());
            } else {
                Serial.println("\nparsed json");

                // ---- Configuration Variables ----
                strcpy(config_server, jsonDoc["config_server"]);
                strcpy(config_port, jsonDoc["config_port"]);
                strcpy(config_name, jsonDoc["config_name"]);
                // ---- END Configuration Variables ----
            }
            configFile.close();
            }
        }
    } else {
        Serial.println("failed to mount FS");
    }
    //end read
}

void saveConfig() {
    Serial.println("Saving Config.");
    DynamicJsonDocument jsonDoc(1024);

    // ---- Configuration Variables ----
    jsonDoc["config_server"] = config_server;
    jsonDoc["config_port"] = config_port;
    jsonDoc["config_name"] = config_name;
    // ---- END Configuration Variables ----

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile)
        Serial.println("Failed to open config file for writing...");
    serializeJson(jsonDoc, Serial);
    serializeJson(jsonDoc, configFile);
    configFile.close();
}

void setupWifiManager() {
    // ---- Configuration Variables ----
    WiFiManagerParameter param_server("server", "Server Hint", config_server, 40);
    WiFiManagerParameter param_port("port", "Server Port Hint", config_port, 6);
    WiFiManagerParameter param_metric("name", "Name Hint", config_name, 40);
    // ---- END Configuration Variables ----
    WiFiManager wifiManager;
    wifiManager.setSaveConfigCallback(saveConfigCallback);
    // ---- Configuration Variables ----
    wifiManager.addParameter(&param_server);
    wifiManager.addParameter(&param_port);
    wifiManager.addParameter(&param_metric);
    // ---- END Configuration Variables ----
    wifiManager.autoConnect();
    // Read parameters
    // ---- Configuration Variables ----
    strcpy(config_server, param_server.getValue());
    strcpy(config_port, param_port.getValue());
    strcpy(config_name, param_metric.getValue());
    // ---- END Configuration Variables ----
}