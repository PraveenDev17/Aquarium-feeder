#include <SoftwareSerial.h>

char rxdata;
char comment[50];

String data;
String string1;
String string2;
String string3;
String string4;
String string5;
String string6;
String string7;

int x1;
int x2;
int x3;
int x4;
int x5;
int x6;
int x7;
int line;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
while(Serial.available())
{  rxdata = Serial.read();
   Serial.print(rxdata);
  if(rxdata == '\r'||rxdata == '\n')
  {
    data = String(comment);
    if(data.length()>0)
    {
    Serial.print("Given:");
    Serial.println(data);
    delay(1000);
    
    x1 = data.indexOf(",");
    x2 = data.indexOf(",",x1+1);
    x3 = data.indexOf(",",x2+1);
    x4 = data.indexOf(",",x3+1);
    x5 = data.indexOf(",",x4+1);
    x6 = data.indexOf(",",x5+1);
    x7 = data.indexOf("\n",x6+1);
    
    string1 = data.substring(0,x1);
    string2 = data.substring(x1+1,x2);
    string3 = data.substring(x2+1,x3);
    string4 = data.substring(x3+1,x4);
    string5 = data.substring(x4+1,x5);
    string6 = data.substring(x5+1,x6);
    string7 = data.substring(x6+1,x7);
    
    
    Serial.print("string1:");Serial.println(string1);
    Serial.print("string2:");Serial.println(string2);
    Serial.print("string3:");Serial.println(string3);
    Serial.print("string4:");Serial.println(string4);
    Serial.print("string5:");Serial.println(string5);
    Serial.print("string6:");Serial.println(string6);
    Serial.print("string7:");Serial.println(string7);
    Serial.println();  

    //rtc starts here
    


    
  }
  for(int i=0;i<sizeof(comment);i++)
  {
    comment[i]=char(0);
  }
  line=0;
  }
  else
  {
    comment[line++] = rxdata;
  }
}
}
