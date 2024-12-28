#include "wifi_connection.h"

WiFiConnection::WiFiConnection() {}

WiFiConnection::~WiFiConnection() {}

void WiFiConnection::connect()
{
    unsigned int timeout = 30000;
    unsigned long start = millis();

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        if (start < (timeout + start))
        {
            Serial.println("Connecting to WiFi...");
            delay(500);
        }
        else
        {
            ESP.restart();
        }
    }
}

void WiFiConnection::disconnect()
{
    WiFi.disconnect();
}

bool WiFiConnection::isConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

String WiFiConnection::sendWaterData(JsonDocument doc)
{
    HTTPClient http;
    String endpoint = "http://deviwms.site:3000/api/datawater"; // Ganti dengan endpoint yang sesuai
    http.begin(endpoint);
    http.addHeader("Content-Type", "application/json");

    String json = "";
    serializeJson(doc, json);

    int httpCode = http.POST(json);
    if (httpCode > 0)
    {
        String response = http.getString();
        return response;
    }
    else
    {
        counterHTTP++;
        if (counterHTTP > 10)
        {
            ESP.restart();
        }
    }
    return "";
}

// String WiFiConnection::sendSupabase(JsonDocument doc)
// {
//     HTTPClient http;
//     String endpoint = String(supabaseUrl) + "/rest/v1/" + tableName;
//     http.begin(endpoint);
//     http.addHeader("Content-Type", "application/json");
//     http.addHeader("apikey", supabaseKey);
//     http.addHeader("Authorization", "Bearer " + String(supabaseKey));

//     String json = "";
//     serializeJson(doc, json);
//     int httpCode = http.POST(json);
//     Serial.print("HTTP Code: ");
//     Serial.println(httpCode);

//     if (httpCode > 0)
//     {
//         String response = http.getString();
//         return response;
//     }
//     else
//     {
//         counterHTTP++;
//         if (counterHTTP > 10)
//         {
//             ESP.restart();
//         }
//     }
//     return "";
// }