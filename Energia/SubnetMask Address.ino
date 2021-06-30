/*************************************************************
    This is the code by Saurabh Lanje.
    YouTube Channel - www.youtube.com/saurabhlanje
    Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/
 
#include<SPI.h>
#include<WiFi.h>
char ssid[]="SSID";
char password[]="PASS";
IPAddress subnet;

void setup() 
{
  // put your setup code here, to run once:
Serial.begin(9600);

Serial.print("Attempt to connect:");
Serial.println(ssid);

WiFi.begin(ssid,password);
while(WiFi.status()!=WL_CONNECTED)
{
  Serial.print(".");
  delay(500);
}
Serial.println("\n you are connected to the Network");

while(WiFi.localIP()==INADDR_NONE)
{
  Serial.print(".");
  delay(300);
}

subnet=WiFi.subnetMask();
Serial.print("subnet mask Address: ");
Serial.println(subnet);

}

void loop() {
  // put your main code here, to run repeatedly:  
}
