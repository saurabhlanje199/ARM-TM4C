/*************************************************************
  WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 9.

 If the IP address of your WiFi is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * CC3200 WiFi LaunchPad or CC3100 WiFi BoosterPack
   with TM4C or MSP430 LaunchPad
   
    This is the code by Saurabh Lanje.
    YouTube Channel - www.youtube.com/saurabhlanje
    Linkedin - www.linkedin.com/in/saurabhlanje
    
 ******************************************************************/

#ifndef __CC3200R1M1RGC__
// Do not include SPI for CC3200 LaunchPad
#define LS 40
#define RS 39
#define LD 29
#define RD 30
#define SLPL 11
#define SLPR 31
#include <SPI.h>
#endif
#include <WiFi.h>

// your network name also called SSID
char ssid[] = "SSID";
// your network password
char password[] = "Pass";
// your network key Index number (needed only for WEP)
int keyIndex = 0;

WiFiServer server(80);

void setup() {
  Serial.begin(115200);      // initialize serial communication
  pinMode(RED_LED, OUTPUT);      // set the LED pin mode

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
  
  // you're connected now, so print out the status  
  printWifiStatus();

  Serial.println("Starting webserver on port 80");
  server.begin();                           // start the web server on port 80
  Serial.println("Webserver started!");

pinMode(LD,OUTPUT);
pinMode(RD,OUTPUT);
pinMode(SLPL,OUTPUT);
pinMode(SLPR,OUTPUT);
digitalWrite(SLPL , HIGH);
digitalWrite(SLPR ,HIGH);
  
}

void loop() {
  int i = 0;
  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    char buffer[150] = {0};                 // make a buffer to hold incoming data
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (strlen(buffer) == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.println("<html><head><title>Energia CC3200 WiFi Web Server</title></head><body align=center>");
            client.println("<h1 align=center><font color=\"red\">Welcome to the CC3200 WiFi Web Server</font></h1>");
            client.print("RED LED <button onclick=\"location.href='/H'\">HIGH</button>");
            client.println(" <button onclick=\"location.href='/L'\">LOW</button><br>");
            client.print("ROBOT movement <button onclick=\"location.href='/A'\">FORWARD</button>");
            client.println(" <button onclick=\"location.href='/B'\">BACKWARD</button><br>");
            client.print("Robot Movement <button onclick=\"location.href='/C'\">RIGHT</button>");
            client.println(" <button onclick=\"location.href='/D'\">LEFT</button><br>");
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear the buffer:
            memset(buffer, 0, 150);
            i = 0;
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          buffer[i++] = c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (endsWith(buffer, "GET /H")) {
          digitalWrite(RED_LED, HIGH);               // GET /H turns the LED on
        }
        if (endsWith(buffer, "GET /L")) {
          digitalWrite(RED_LED, LOW);                // GET /L turns the LED off
        }
        if (endsWith(buffer, "GET /A")) {
              digitalWrite(LD , LOW);
              digitalWrite(RD ,LOW);
              analogWrite(LS  ,20);
              analogWrite(RS  ,20); 
              delay(1000);// GET /H turns the LED on
        }
        if (endsWith(buffer, "GET /B")) {
         
           digitalWrite(LD , HIGH);
              digitalWrite(RD ,HIGH);
              analogWrite(LS  ,20);
              analogWrite(RS  ,20);
              delay(1000);// GET /L turns the LED off
        }
        if (endsWith(buffer, "GET /C")) {
            digitalWrite(LD , LOW);
            digitalWrite(RD ,LOW);
            analogWrite(LS  ,20);
            analogWrite(RS  ,0);
            delay(1000); // GET /H turns the LED on
        }
        if (endsWith(buffer, "GET /D")) {
               digitalWrite(LD , LOW);
              digitalWrite(RD ,LOW);
             analogWrite(LS  ,0);
             analogWrite(RS  ,20);
              delay(1000);         // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

//
//a way to check if one array ends with another array
//
boolean endsWith(char* inString, const char* compString) {
  int compLength = strlen(compString);
  int strLength = strlen(inString);
  
  //compare the last "compLength" values of the inString
  int i;
  for (i = 0; i < compLength; i++) {
    char a = inString[(strLength - 1) - i];
    char b = compString[(compLength - 1) - i];
    if (a != b) {
      return false;
    }
  }
  return true;
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
