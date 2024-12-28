// #include <Arduino.h>
// #include <Adafruit_ADS1X15.h>
// #include <SPI.h>
// #include <TinyGPSPlus.h>
// #include <ArduinoJson.h>
// #include <esp_task_wdt.h>
// #include <WiFi.h>
// #include <HTTPClient.h>

// #define WDT_TIMEOUT 15
// #define VREF 5.0  // analog reference voltage(Volt) of the ADC
// #define SCOUNT 30 // sum of sample point

// Adafruit_ADS1115 ads_batt;
// Adafruit_ADS1115 ads_tds;
// Adafruit_ADS1115 ads_ntu;
// TinyGPSPlus gps;
// JsonDocument doc;

// const char *ssid = "Subhanallah";			 // WiFi SSID
// const char *password = "muhammadnabiyullah"; // WiFi Password
// int analogBuffer[SCOUNT];					 // TDS sensor
// int analogBufferTemp[SCOUNT];				 // TDS sensor
// int analogBufferIndex = 0, copyIndex = 0;	 // TDS sensor
// float averageVoltage = 0, temperature = 29;	 // TDS sensor
// unsigned char data[4] = {};					 // store the received data for the ultrasonic sensor
// byte counterHTTP = 0;						 // store the counter for the HTTP request
// float tdsValue = 0, ntuValue = 0, battValue = 0, waterLevelValue = 0, latitude = 0, longitude = 0;

// float getValueNTU();
// float getWaterLevel(HardwareSerial &serial);
// float getValueTDS();
// float getValueBatt();
// void updateValueTDS();
// void updateValueNTU();
// void updateValueWaterLevel();
// void updateValueBatt();
// void updateValueGPS();

// unsigned long previousMillis = 0; // Stores the last time the sensors were updated
// const long interval = 10000;	  // Interval at which to update the sensors (1 second)

// void setup()
// {
// 	Serial.begin(115200);
// 	Serial1.begin(9600, SERIAL_8N1, 19, 18);
// 	Serial2.begin(9600);
// 	esp_task_wdt_init(WDT_TIMEOUT, true); // enable panic so ESP32 restarts
// 	esp_task_wdt_add(NULL);				  // add current thread to WDT watch
// 	WiFi.begin(ssid, password);
// 	while (WiFi.status() != WL_CONNECTED)
// 	{
// 		Serial.println("Connecting to WiFi...");
// 		delay(1000);
// 	}
// 	ads_tds.setGain(GAIN_TWOTHIRDS);
// 	ads_batt.setGain(GAIN_TWOTHIRDS);
// 	ads_ntu.setGain(GAIN_TWOTHIRDS);
// 	ads_batt.begin();
// 	ads_tds.begin();
// 	ads_ntu.begin();
// }

// void loop()
// {
// 	updateValueTDS();
// 	updateValueBatt();
// 	updateValueNTU();
// 	updateValueWaterLevel();
// 	updateValueGPS();
// 	esp_task_wdt_reset(); // reset the WDT timer

// 	unsigned long currentMillis = millis();
// 	if (currentMillis - previousMillis >= interval)
// 	{
// 		previousMillis = currentMillis;
// 		if (WiFi.status() == WL_CONNECTED)
// 		{
// 			HTTPClient http;
// 			http.begin("http://deviwms.site:3000/api/datawater");
// 			http.addHeader("Content-Type", "application/json");

// 			String json = "";
// 			doc["device_name"] = "water1";
// 			doc["latitude"] = String(-6.985818);
// 			doc["longitude"] = String(110.441178);
// 			doc["tma"] = waterLevelValue;
// 			doc["tds"] = tdsValue;
// 			doc["ph"] = 0.0;
// 			doc["suhu"] = 0.0;
// 			doc["kejernihan"] = getValueNTU();
// 			doc["debit"] = 0;
// 			doc["voltase"] = battValue;
// 			serializeJson(doc, json);

// 			int httpCode = http.POST(json);
// 			if (httpCode > 0)
// 			{
// 				String response = http.getString();
// 				Serial.println(httpCode); // Print HTTP return code
// 				Serial.println(response); // Print request response payload
// 				counterHTTP = 0;		  // Reset counter
// 			}
// 			else
// 			{
// 				Serial.print("Error on sending POST: ");
// 				Serial.println(httpCode);
// 				counterHTTP++;
// 			}
// 			if (counterHTTP > 10) // If the HTTP request fails 10 times, restart the ESP32
// 				while (1)
// 					;
// 			http.end(); // Free resources
// 		}
// 	}
// }

// float getValueNTU()
// {
// 	float ntuVoltage = ads_ntu.computeVolts(ads_ntu.readADC_SingleEnded(1));
// 	return ntuVoltage;
// }

// void updateValueNTU()
// {
// 	ntuValue = -1120.4 * getValueNTU() * getValueNTU() + 5742.3 * getValueNTU() - 4352.9;
// }

// float getWaterLevel(HardwareSerial &serial)
// {
// 	do
// 	{
// 		for (int i = 0; i < 4; i++)
// 		{
// 			data[i] = serial.read();
// 		}
// 	} while (serial.read() == 0xff);

// 	serial.flush();

// 	float distance = 0;
// 	if (data[0] == 0xff)
// 	{
// 		int sum;
// 		sum = (data[0] + data[1] + data[2]) & 0x00FF;
// 		if (sum == data[3])
// 		{
// 			distance = (data[1] << 8) + data[2];
// 			if (distance > 280)
// 			{
// 				return distance / 10;
// 			}
// 			else
// 			{
// 				return -1; // Below Lower Limit
// 			}
// 		}
// 	}
// 	return waterLevelValue;
// }

// void updateValueWaterLevel()
// {
// 	waterLevelValue = getWaterLevel(Serial2);
// }

// float getValueBatt()
// {
// 	return ads_batt.computeVolts(ads_batt.readADC_SingleEnded(0));
// }

// void updateValueBatt()
// {
// 	battValue = getValueBatt();
// }

// void updateValueGPS()
// {
// 	while (Serial1.available() > 0)
// 	{
// 		gps.encode(Serial1.read());
// 		if (gps.location.isValid())
// 		{
// 			latitude = gps.location.lat();
// 			longitude = gps.location.lng();
// 		}
// 	}
// }

// float getValueTDS()
// {
// 	return ads_tds.computeVolts(ads_tds.readADC_SingleEnded(2));
// }

// int getMedianNum(int bArray[], int iFilterLen);

// void updateValueTDS()
// {
// 	static unsigned long analogSampleTimepoint = millis();
// 	if (millis() - analogSampleTimepoint > 40U) // every 40 milliseconds,read the analog value from the ADC
// 	{
// 		analogSampleTimepoint = millis();
// 		analogBuffer[analogBufferIndex] = ads_tds.readADC_SingleEnded(2); // read the analog value and store into the buffer
// 		analogBufferIndex++;
// 		if (analogBufferIndex == SCOUNT)
// 			analogBufferIndex = 0;
// 	}
// 	static unsigned long printTimepoint = millis();
// 	if (millis() - printTimepoint > 800U) // every 800 milliseconds, calculate the TDS value
// 	{
// 		printTimepoint = millis();
// 		for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++)
// 			analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
// 		averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 32768.0;																								 // read the analog value more stable by the median filtering algorithm, and convert to voltage value
// 		float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);																												 // temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0));
// 		float compensationVolatge = averageVoltage / compensationCoefficient;																											 // temperature compensation
// 		tdsValue = (133.42 * compensationVolatge * compensationVolatge * compensationVolatge - 255.86 * compensationVolatge * compensationVolatge + 857.39 * compensationVolatge) * 0.5; // convert voltage value to tds value
// 	}
// }

// int getMedianNum(int bArray[], int iFilterLen)
// {
// 	int bTab[iFilterLen];
// 	for (byte i = 0; i < iFilterLen; i++)
// 		bTab[i] = bArray[i];
// 	int i, j, bTemp;
// 	for (j = 0; j < iFilterLen - 1; j++)
// 	{
// 		for (i = 0; i < iFilterLen - j - 1; i++)
// 		{
// 			if (bTab[i] > bTab[i + 1])
// 			{
// 				bTemp = bTab[i];
// 				bTab[i] = bTab[i + 1];
// 				bTab[i + 1] = bTemp;
// 			}
// 		}
// 	}
// 	if ((iFilterLen & 1) > 0)
// 		bTemp = bTab[(iFilterLen - 1) / 2];
// 	else
// 		bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
// 	return bTemp;
// }
