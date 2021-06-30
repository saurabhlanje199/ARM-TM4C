/*************************************************************
    This is the code by Saurabh Lanje.
    YouTube Channel - www.youtube.com/saurabhlanje
    Linkedin - www.linkedin.com/in/saurabhlanje
 *************************************************************/
 
#define LED RED_LED

void setup()
 {                
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
}

void loop()
 {
  digitalWrite(RED_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(RED_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(500);               // wait for a second

  digitalWrite(BLUE_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(BLUE_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(500); 

  digitalWrite(GREEN_LED, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);               // wait for a second
  digitalWrite(GREEN_LED, LOW);    // turn the LED off by making the voltage LOW
  delay(500); 
}