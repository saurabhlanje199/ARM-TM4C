/*************************************************************
    This is the code by Saurabh Lanje.
    YouTube Channel - www.youtube.com/saurabhlanje
    Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/

#define LED RED_LED
  
void setup() 
{                
  pinMode(LED, OUTPUT);     
}

void loop() 
{
int i=0;
  for(i=0;i<255;i++)
  {
    analogWrite(LED,i);
    delay(1000);
    i+=25;
    if(i>250)
    {
      for(i=255;i>0;i--)
      {
        analogWrite(LED,i);
        delay(1000);
      }
    }
  }
}