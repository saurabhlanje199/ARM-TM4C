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

void setup()
 {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial1.begin(9600);
pinMode(LD,OUTPUT);
pinMode(RD,OUTPUT);
pinMode(SLPL,OUTPUT);
pinMode(SLPR,OUTPUT);
digitalWrite(SLPL , HIGH);
digitalWrite(SLPR ,HIGH);
}

void loop(){

   char c = 0;
  // put your main code here, to run repeatedly: 
  if(Serial1.available()){
  c = Serial1.read();
  Serial.println(c);
  }
  switch(c)
  {
case 'F' :   digitalWrite(LD , LOW);
              digitalWrite(RD ,LOW);
              analogWrite(LS  ,20);
              analogWrite(RS  ,20);
              delay(1000);
           break;
           
case 'B' :    digitalWrite(LD , HIGH);
              digitalWrite(RD ,HIGH);
              analogWrite(LS  ,20);
              analogWrite(RS  ,20);
              delay(1000);
           break;
           
case 'R' :  digitalWrite(LD , LOW);
            digitalWrite(RD ,LOW);
            analogWrite(LS  ,20);
            analogWrite(RS  ,0);
            delay(1000);
            break;
           
case 'L' :   digitalWrite(LD , LOW);
              digitalWrite(RD ,LOW);
             analogWrite(LS  ,0);
             analogWrite(RS  ,20);
              delay(1000);
           break;
  }
  }
