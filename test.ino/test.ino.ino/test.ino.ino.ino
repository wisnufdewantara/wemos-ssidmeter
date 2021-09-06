#include <ESP8266WiFi.h>
boolean networkPresent;
const char* ssid = "AndroidAP";
const char* password = "12345678";
int absRssi;

void setup() {
  Serial.begin(115200); 
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1)
 
  { 
      Serial.println("Couldn't get a wifi connection");
    networkPresent=false;
    while(true);
 
  } 
  networkPresent=false;
 
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    String ssidComparison=WiFi.SSID(thisNet);
    if(ssidComparison.equals(ssid)){
      int rssi=WiFi.RSSI(thisNet);
      int tempRssi=abs(rssi);
      //      Serial.println(tempRssi);     
      if (tempRssi>11&&tempRssi<100){
        absRssi=tempRssi;
        networkPresent=true;
        Serial.print(" RSSI   ");
        Serial.println(absRssi);
      }
      if (tempRssi==4370){
        absRssi=10;
        Serial.println("Error on 4370"); 
      }
    }
  }


}

void loop() {
  // put your main code here, to run repeatedly:

}
