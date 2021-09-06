#include <FastLED.h>
#include <ESP8266WiFi.h>
  #define NUM_LEDS 8
  #define DATA_PIN D6
  int maxRssi=20;
  int minRssi=100;
  int absRssi;
  boolean networkPresent;
  String ssidTarget = "Mi Phone";
  CRGB leds[NUM_LEDS];
  unsigned long time = millis();
void setup()
{
  Serial.begin(115200);
  Serial.println();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  scanNetworks();
  Serial.print("Time setup: ");
  Serial.println(time);
}

 void loop() {
  scanNetworks();
  if (networkPresent==false||absRssi==0){
    Serial.println("No internet connection, Led doesn't work");
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
    leds[dot] = CRGB::Red;
    FastLED.show();
    delay (50);
    leds[dot] = CRGB::Black;
    FastLED.show();
    delay (10);
        }  
    }
   else {
    convertValues();
    } 
}

//-------------------------------------------------------------
   
void scanNetworks() {
  // scan for nearby networks:
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
    if(ssidComparison.equals(ssidTarget)){
      int rssi=WiFi.RSSI(thisNet);
      int tempRssi=abs(rssi);     
      if (tempRssi>11&&tempRssi<100){
        absRssi=tempRssi;
        networkPresent=true;
        Serial.print(" RSSI   " + WiFi.SSID(thisNet));
        Serial.println(WiFi.RSSI(thisNet));
      }
    }
  }
}
//--------------------------------------------------------------
void convertValues(){
  networkPresent=true;
  if(absRssi>=maxRssi&&absRssi<=50){
  Serial.println("Kuat"); 
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
      leds[dot] = CRGB::Green;
      FastLED.show();
      }
  }
  else if(absRssi>=51&&absRssi<=60){ 
  Serial.println("Agak Kuat");
  for(int dot = 0; dot < NUM_LEDS; dot++) {
      leds[dot] = CRGB::GreenYellow;
      FastLED.show();
      } 
  }
  else if(absRssi>=61&&absRssi<=70){ 
  Serial.println("Cukup");
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
      leds[dot] = CRGB::Yellow;
      FastLED.show();
      } 
  }
  else if(absRssi>=71&&absRssi<80){ 
  Serial.println("Lemah");
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
      leds[dot] = CRGB::Orange;
      FastLED.show();
      } 
  }
  else if(absRssi>=81&&absRssi<89){ 
  Serial.println("Lemah Sekali");
  for(int dot = 0; dot < NUM_LEDS; dot++) { 
      leds[dot] = CRGB::OrangeRed;
      FastLED.show();
      } 
  }
  else { 
    Serial.println("Nihil");
    for(int dot = 0; dot < NUM_LEDS; dot++) { 
      leds[dot] = CRGB::Red;
      FastLED.show();
    } 
  }
}   
