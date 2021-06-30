/*************************************************************
    This is the code by Saurabh Lanje.
    YouTube Channel - www.youtube.com/saurabhlanje
    Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/
 
#define LED RED_LED
  
void setup() 
{                
  pinMode(LED, OUTPUT);     
  pinMode(PUSH1,INPUT_PULLUP);
}

void loop() 
{
  if(digitalRead(PUSH1)==0)
  {
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  }
  else
  {
  digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
}