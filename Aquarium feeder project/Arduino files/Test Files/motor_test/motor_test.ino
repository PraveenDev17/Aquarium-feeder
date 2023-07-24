#include <L298N.h>     
int i;

void setup() {
pinMode(10,INPUT);
// analog Pin 10 as Input Pin for Motor A
Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

while(i<1)// number is second value
{// Pin 10 is High for Motor A
analogWrite(10,200);
delay(1000);
Serial.println(i);
i=i+1;
}
analogWrite(10,0);
delay(4000);

}
