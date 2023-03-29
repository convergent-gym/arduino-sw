#include "NewPing.h"
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid="utexas-iot";
const char* password="37330697708772156687";


// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 400  
#define TRIGGER_PIN 12
#define ECHO_PIN 13 
// NewPing setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);


void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while(WiFi.status() != WL_CONNECTED){
  Serial.print(".");
  delay(500);
  }
  Serial.println("\nConnected to the WiFi network");
  Serial.print(WiFi.localIP());
}


void loop() {
  HTTPClient http;
  http.begin("http://webhook.site/18a9790d-21e8-4c2d-b6a3-38f260945284");
  http.addHeader("Content-Type", "application/json");

  
  Serial.print("Distance = ");
  Serial.print(sonar.ping_cm());
  Serial.println(" cm");

  http.POST("{ \"machineId\": \"587e5c7f-6d01-44f1-bf2f-c588a7a72627\", \"distance\": \""+String(sonar.ping_cm())+"\", \"authKey\":\"bWFya2V0IGZyYW5rZm9yZA==\"}");
  delay(1000);
}
