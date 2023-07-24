void setup() {
  // put your setup code here, to run once:
pinMode(13, OUTPUT);
pinMode(4,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(4)==LOW)
{
  digitalWrite(13,HIGH);
  Serial.print("Movement detected \n");
  delay(500);
}
else
digitalWrite(13,LOW);
}
