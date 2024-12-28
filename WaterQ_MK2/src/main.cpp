#include <Arduino.h>
#include <esp_task_wdt.h>
#include <TaskScheduler.h>
#include <ArduinoJson.h>
#include "sensor.h"
#include "ads_1152.h"
#include "a01nyub.h"
#include "tds.h"
#include "ntu.h"
#include "batt.h"
#include "gps.h"
#include "wifi_connection.h"

#define WDT_TIMEOUT 30

ADS1152 BATT_ADC; // Range 0 - 6V, A1 - COMP_0_GND
ADS1152 NTU_ADC;  // Range 0 - 6V, A1 - COMP_1_GND
ADS1152 TDS_ADC;  // Range 0 - 6V, A0 - COMP_2_GND
A01NYUB waterLevel;
float HIGHMAX = 300.0;
TDS tds;
NTU ntu;
GPS gps;
BATT batt;
WiFiConnection wifi;
JsonDocument doc;

void taskUpdater();
void taskSampling();
void taskLogger();

Task updaterTask(1, TASK_FOREVER, &taskUpdater);
Task samplingTask(10000, TASK_FOREVER, &taskSampling);
Task loggerTask(5000, TASK_FOREVER, &taskLogger);
Scheduler runner;

void setup()
{
	Serial.begin(115200);
	Serial1.begin(9600, SERIAL_8N1, 18, 19);
	Serial2.begin(9600);
	wifi.connect();

	esp_task_wdt_init(WDT_TIMEOUT, true); // enable panic so ESP32 restarts
	esp_task_wdt_add(NULL);				  // add current thread to WDT watch

	BATT_ADC.init(GAIN_TWOTHIRDS, 0);
	NTU_ADC.init(GAIN_TWOTHIRDS, 1);
	TDS_ADC.init(GAIN_TWOTHIRDS, 2);

	runner.init();
	runner.addTask(updaterTask);
	runner.addTask(samplingTask);
	runner.addTask(loggerTask);

	updaterTask.enable();
	samplingTask.enable();
	loggerTask.enable();
}

void loop()
{
	esp_task_wdt_reset(); // reset the WDT timer
	runner.execute();
}

void taskUpdater()
{
	tds.updateValue(TDS_ADC);
	ntu.updateValue(NTU_ADC);
	gps.updateData(Serial1);
	batt.updateValue(BATT_ADC);
	waterLevel.updateValue(Serial2,HIGHMAX);
}

void taskSampling()
{
	doc["device_name"] = "water2";
	doc["latitude"] = String(gps.getLatitude(), 7) == "0.0000000" ? "-6.9932 " : String(gps.getLatitude(), 7);
	doc["longitude"] = String(gps.getLongitude(), 7) == "0.0000000" ? "100.086974" : String(gps.getLongitude(), 7);
	doc["tma"] = waterLevel.getValue();
	doc["ph"] = 0;
	doc["suhu"] = 0;
	doc["kejernihan"] = ntu.getValue();
	doc["debit"] = 0;
	doc["tds"] = tds.getValue();
	doc["voltase"] = batt.getValue();
}

void taskLogger()
{
	if (wifi.isConnected())
	{
		String response = wifi.sendWaterData(doc);
		Serial.println(response);
	}
	else
	{
		wifi.connect();
	}
}