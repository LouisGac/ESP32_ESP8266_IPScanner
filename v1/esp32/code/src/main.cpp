/*
*
* ESP32 IPScanner
* Project to implement WIFI network IP Address Scanner in ESP32 boards
* 
* Tested with ESP Lolin32 board
* Developed by Walid Amriou
* Website: www.walidamriou.com
* Email: contact@walidmariou.com 
*
*/

#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Ping.h>
#include <string>

const char* ssid = "ssid";
const char* password = "password";

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println();
  Serial.println("Connecting to WiFi");
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("WiFi connected with ip ");
  Serial.println(WiFi.localIP());

  // Network Scanner 
  IPAddress ip = WiFi.localIP();
  String ip_body = "";
  ip_body=ip_body+ip[0]+"."+ip[1]+"."+ip[2]+".";
  String ip_body_string;
  const char *remote_host;
  String IPs_list[255];
  int number_of_IPs=0;
  for (int i = 0; i < 255; i++){
    ip_body_string = ip_body+i;
    remote_host=ip_body_string.c_str();
    Serial.print("Pinging host ");
    Serial.println(remote_host);
    if(Ping.ping(remote_host)) {
      Serial.println("There is a Device connected with this IP");
      IPs_list[number_of_IPs]=ip_body_string;
      number_of_IPs++;
    } 
    else {
      Serial.println("No Device connected with this IP");
    }
  }

  Serial.println("The number of connected device in this network: ");
  Serial.print(number_of_IPs);

  Serial.println("The IP List of connected device in this network:");
  for (int i = 0; i < number_of_IPs; i++){
    Serial.println(IPs_list[i]);
  }
  
}

void loop() { }
