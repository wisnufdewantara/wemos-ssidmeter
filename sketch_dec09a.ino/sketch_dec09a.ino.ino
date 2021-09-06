/*
  RSSI : (0) / (-50) = Kuat Banget = 
  RSSI : (-51) / (-60) = Kuat  = 
  RSSI : (-61) / (-71) = Cukup = 
  RSSI : (-72) / (-81) = Lemah = 
  RSSI : (-82) / (-89) = Lemah Banget =
  RSSI : (-90) / (++) = Nihil =
*/

#include <ESP8266WiFi.h>

const char* ssid = "Mi Phone";
const char* password = "satusampaidelapan";


void setup(void)
{
  Serial.begin(115200);
  Serial.println();

  Serial.printf("Connecting to %s\n", ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(5);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print(WiFi.RSSI());
}

void loop() {
  Serial.print(WiFi.RSSI());
  delay (1000);

}
