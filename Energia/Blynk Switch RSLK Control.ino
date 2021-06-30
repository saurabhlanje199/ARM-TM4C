/*************************************************************
    This is the code by Saurabh Lanje.
    YouTube Channel - www.youtube.com/saurabhlanje
    Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/

#define LS 40
#define RS 39
#define LD 29
#define RD 30
#define SLPL 11
#define SLPR 31

    #define BLYNK_PRINT Serial


    #include <SPI.h>
    #include <WiFi.h>
    #include <BlynkSimpleEnergiaWiFi.h>

//Global Varibles
int ld=0,rd=0;
int leftspeed=0,rightspeed=0;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
   char auth[] = "Auth Token";

// Your WiFi credentials.
// Set password to "" for open networks.
   char ssid[] = "SSID";
   char pass[] = "Pass";


  void setup()
 {
    Serial1.begin(9600);
    pinMode(LD,OUTPUT);
    pinMode(RD,OUTPUT);
    pinMode(SLPL,OUTPUT);
    pinMode(SLPR,OUTPUT);
    digitalWrite(SLPL , HIGH);
    digitalWrite(SLPR ,HIGH);
    Serial.begin(9600);
    pinMode(RED_LED, OUTPUT);
    Blynk.begin(auth, ssid, pass);

 }
    BLYNK_WRITE(V0){
     int data = param.asInt();
     if(data == 1){
      ld = rd = 0;
      leftspeed = rightspeed = 30;
     }
  else{
     leftspeed = rightspeed = 0;
  }
  digitalWrite(LD,ld);
  digitalWrite(RD,rd);
  analogWrite(LS,leftspeed);
  analogWrite(RS,rightspeed);
    }

    BLYNK_WRITE(V1){
     int data = param.asInt();
     if(data == 1){
      ld = rd = 1;
      leftspeed = rightspeed = 30;
     }
  else{
     leftspeed = rightspeed = 0;
  }
  digitalWrite(LD,ld);
  digitalWrite(RD,rd);
  analogWrite(LS,leftspeed);
  analogWrite(RS,rightspeed);
    }

    BLYNK_WRITE(V2){
     int data = param.asInt();
     if(data == 1){
      ld = rd = 0;
      leftspeed = 0;
      rightspeed = 30;
     }
  else{
     leftspeed = rightspeed = 0;
  }
  digitalWrite(LD,ld);
  digitalWrite(RD,rd);
  analogWrite(LS,leftspeed);
  analogWrite(RS,rightspeed);
    }

    BLYNK_WRITE(V3){
     int data = param.asInt();
     if(data == 1){
      ld = rd = 0;
      leftspeed = 30;
      rightspeed = 0;
     }
  else{
     leftspeed = rightspeed = 0;
  }
  digitalWrite(LD,ld);
  digitalWrite(RD,rd);
  analogWrite(LS,leftspeed);
  analogWrite(RS,rightspeed);
    }


  void loop()
  {
   Blynk.run();
  }
