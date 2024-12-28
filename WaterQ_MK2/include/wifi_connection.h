#ifndef WIFI_H
#define WIFI_H

#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJSON.h>

class WiFiConnection
{
private:
    byte counterHTTP = 0;
    const char *ssid = "Subhanallah";
    const char *password = "muhammadnabiyullah";
    const char *apiEndpoint = "http://deviwms.site:3000/api/datawater";
    // const char *supabaseUrl = "https://qqwbholpjtwptvqwfyhy.supabase.co";
    // const char *supabaseKey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6InFxd2Job2xwanR3cHR2cXdmeWh5Iiwicm9sZSI6InNlcnZpY2Vfcm9sZSIsImlhdCI6MTcyMzEwNjQ1NiwiZXhwIjoyMDM4NjgyNDU2fQ.sHK3cuZL1_rq3bOpFhu5m-wVLHDKSjYSZRKNKqhSHGA";
    // const char *tableName = "water_test";

public:
    WiFiConnection();
    ~WiFiConnection();
    void connect();
    void disconnect();
    bool isConnected();
    String sendWaterData(JsonDocument doc);
    // String send(JsonDocument doc);
    // String sendSupabase(JsonDocument doc);
};

#endif