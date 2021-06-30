/*************************************************************
    This is the code by Saurabh Lanje.
    YouTube Channel - www.youtube.com/saurabhlanje
    Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/

void setup() 
{
Serial.begin(9600);
}

void loop()
{
  int a;
  char ch[4];
  a=analogRead(A0);
  
  Serial.println(a);
  delay(1000);
 }
