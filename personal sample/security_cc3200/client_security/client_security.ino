/*
  Web client
 This sketch connects to a website (http://www.google.com)
 using a WiFi shield.
 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.
 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.
 Circuit:
 * WiFi shield attached
 created 13 July 2010
 by dlf (Metodo2 srl)
 modified 31 May 2012
 by Tom Igoe
 */


#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#include <SPI.h>
#endif
#include <WiFi.h>

// your network name also called SSID
char ssid[] = "energia";
// your network password
char password[] = "launchpad";
int trigger=7;
// if you don't want to use DNS (and reduce your sketch size)
// use the numeric IP instead of the name for the server:
//IPAddress server(50,62,217,1);  // numeric IP for Google (no DNS)
byte server2[] = { 192, 168, 1, 1 };    // name address for Google (using DNS)

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
WiFiClient client;

void setup() {
  //Initialize serial and wait for port to open:
    pinMode(RED_LED, OUTPUT);      // set the LED pin mode
    digitalWrite(RED_LED, LOW);
    pinMode(GREEN_LED, OUTPUT);      // set the LED pin mode
    digitalWrite(GREEN_LED, LOW);
    pinMode(YELLOW_LED, OUTPUT);      // set the LED pin mode
    digitalWrite(YELLOW_LED, LOW);
    
    pinMode(trigger,INPUT_PULLUP);      // set the LED pin mode
    digitalWrite(YELLOW_LED, LOW);
    
  Serial.begin(115200);

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");
  
  while (WiFi.localIP() == INADDR_NONE) {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }

  Serial.println("\nIP Address obtained");
  printWifiStatus();

  Serial.println("\nStarting connection to server...");
  // if you get a connection, report back via serial:
  byte server2[] = { 192, 168, 1, 1 };
  if (client.connect(server2, 80)) {
    Serial.println("connected to server");
    // Make a HTTP request:
    
  }
}

void loop() {
  Serial.println("loop");
// WiFi.begin(ssid, password);
 byte server2[] = { 192, 168, 1, 1 };
 client.connect(server2, 80);
  
    while(client.connected())
    {
       digitalWrite(GREEN_LED,HIGH);
       digitalWrite(YELLOW_LED,LOW);
      Serial.print("still connected");
          for(int i=0;i<100;i++)
          {
           /*  client.println("GET /GH");
             delay(100);
             client.println("GET /GL");
             delay(100);
             if(!client.connected())
             {
               break;
             }
             */
             Serial.print(digitalRead(trigger));
             
             if(digitalRead(trigger)!=0){
             client.println("GET /RH");
             delay(50);
             }
             
          }
    }
   
  

  // if the server's disconnected, stop the client:
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting from server.");
    client.stop();
    digitalWrite(YELLOW_LED,HIGH);
    digitalWrite(GREEN_LED,LOW);
    // do nothing forevermore:
    
  }
}


void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
