/*************************************************************
    This is the code by Saurabh Lanje.
    YouTube Channel - www.youtube.com/saurabhlanje
    Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/
 
#include <SPI.h>
#include <WiFi.h>

IPAddress ip(192, 168, 1, 122);  

// your network name also called SSID
char ssid[] = "SSID";
// your network password
char password[] ="Pass";

WiFiServer server(1124);

void setup() 
{
  //Initialize serial and wait for port to open:
  Serial.begin(9600);

 // pinMode(PUSH1,INPUT_PULLUP);

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to Network named: ");
  // print the network name (SSID);
  Serial.println(ssid); 
  // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
  
  WiFi.config(ip);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED) 
  {
    // print dots while we wait to connect
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nYou're connected to the network");
  Serial.println("Waiting for an ip address");

  while (WiFi.localIP() == INADDR_NONE) 
  {
    // print dots while we wait for an ip addresss
    Serial.print(".");
    delay(300);
  }
  Serial.println("\nIP Address obtained");
  // you're connected now, so print out the status:
  printWifiStatus();

  // start the server:
  server.begin();
}

void loop() 
{
  // wait for a new client:
  WiFiClient client = server.available();
 // if(!digitalRead(PUSH1))  //ASSIGNMENT 
  if(client==true)
  {
    server.print("HELLO\n");
    delay(500);
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress IP = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(IP);
}
