/*************************************************************
    This is the code by Saurabh Lanje.
    YouTube Channel - www.youtube.com/saurabhlanje
    Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/
 
#include<String.h>
//Predefined commands to compare the string received from the voice control app
#define START "start"
#define FORWARD "forward"
#define BACKWARD "backward"
#define RIGHT "right"
#define LEFT "left"
#define STOP "stop"
//macro section
#define LS 40
#define RS 39
#define LD 29
#define RD 30
#define SLPL 11
#define SLPR 31

//global variables declaration
int k = 0;
int lmspeed = 0,speedl = 0,ldir = 0,rdir = 0;
int rmspeed = 0,speedr = 0;
char cmd[10] = {"\0"};
char precmd[9][10] = {START,STOP,FORWARD,BACKWARD,LEFT,RIGHT};
char ctl[9] = {'1','2','3','4','5','6'};

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
Serial1.begin(9600);
pinMode(LD, OUTPUT);
pinMode(RD, OUTPUT);
pinMode(SLPL,OUTPUT);
pinMode(SLPR,OUTPUT);
digitalWrite(SLPL,HIGH);
digitalWrite(SLPR,HIGH);  
}

void loop() {
    int i = 0;
// put your main code here, to run repeatedly: 
    if(Serial1.available())
    Serial1.readBytes(cmd,10);  
    //Serial.println(cmd);
    //To identify the command
    for(i = 0;i<9;i++ )
    {
    if((strcmp(cmd,precmd[i])) == 0)
    {
       k = i;
    break;
    }
}
//decision and parameters config part
switch(ctl[k])
{
    case '1' : lmspeed = 20;
               rmspeed = 20;
               digitalWrite(LD,0);
               digitalWrite(RD,0);
               break; 
    case '2' : speedl = 0;
               speedr = 0;
               break;
    case '3' : speedl = lmspeed;
               speedr = rmspeed;
               digitalWrite(LD,0);
               digitalWrite(RD,0);
               break;
    case '4' : speedl = lmspeed;
               speedr = rmspeed;
               digitalWrite(LD,1);
               digitalWrite(RD,1);
               break;   
    case '5' : speedl = 0;
               speedr = rmspeed;
               break;
    case '6' : speedr = 0;
               speedl = lmspeed;
               break;
    default  : speedl = 0;
               speedr = 0;
               break;                     
  }        
analogWrite(LS,speedl);
analogWrite(RS,speedr);
}
