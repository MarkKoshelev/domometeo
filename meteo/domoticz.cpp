#ifdef ESP8266
#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#endif

#ifdef ESP32
#include <WebServer.h>
#include <WiFi.h>
#include <HTTPClient.h>
#endif
#include "domoticz.h"
// based on openWeatherCurrent
// class OpenWeatherMapCurrent

DomoticzCurrent::DomoticzCurrent() {
}

bool DomoticzCurrent::updateCurrent(DomoticzCurrentData* data, const String& url) {
  Serial.printf("updateCurrent");
  return doUpdate(data, url);
}

bool DomoticzCurrent::doUpdate(DomoticzCurrentData* data, const String& url) {
  unsigned long lostTest = 10000UL;
  unsigned long lost_do = millis();
  bool ret=true;
  this->data = data;
  JsonStreamingParser parser;
  parser.setListener(this);

  HTTPClient http;
  http.begin(url);

  bool isBody = false;
  char c;
  int size;
  
  Serial.printf("[HTTP]  GET... %s\n",url.c_str() );
  
  int httpCode = http.GET();
  
  Serial.printf("[HTTP] GET... code: %d\n", httpCode);
  
  if(httpCode == HTTP_CODE_OK) {

    WiFiClient * client = http.getStreamPtr();

    while(client->connected() && client->available()) {
      while((size = client->available()) > 0) {
		if ((millis() - lost_do) > lostTest) {
			Serial.println ("lost in client with a timeout");
			client->stop();
		//	ESP.restart();
		ret=false;;
		break;
	    }
        c = client->read();
        if (c == '{' || c == '[') {
          isBody = true;
        }
        if (isBody) {
          parser.parse(c);
        }
        // give WiFi and TCP/IP libraries a chance to handle pending events
        yield();
      }
    }
  }
  else ret=false;
  
  this->data = nullptr;
  return ret;
}

void DomoticzCurrent::value(String value) {
//  Serial.printf("key: %s, value: %s\n", currentKey.c_str(),value.c_str());

  if (currentKey == "Temp") {
  Serial.printf("key: %s, value: %s\n", currentKey.c_str(),value.c_str());
    this->data->temp = value.toFloat();
  }
  if (currentKey == "Humidity") {
  Serial.printf("key: %s, value: %s\n", currentKey.c_str(),value.c_str());
    this->data->humidity = value.toInt();
  }
  if (currentKey == "Pressure") {
  Serial.printf("key: %s, value: %s\n", currentKey.c_str(),value.c_str());
    this->data->pressure = value.toInt();
  }
  if (currentKey == "cod") {
    this->data->cod = value.toInt();
  }
}

// virtual functions
void DomoticzCurrent::whitespace(char c) {
// Serial.println("whitespace");
}

void DomoticzCurrent::startDocument() {
// Serial.println("start document");
}

void DomoticzCurrent::key(String key) {
  currentKey = String(key);
//  Serial.print("start key: ");  Serial.println(currentKey);
}

void DomoticzCurrent::startObject() {
  currentParent = currentKey;
//  Serial.print("start object, parent: ");  Serial.println(currentParent);
}

void DomoticzCurrent::endObject() {
  currentParent = "";
}

void DomoticzCurrent::endDocument() {
}

void DomoticzCurrent::startArray() {
}

void DomoticzCurrent::endArray() {
}





