#include <SoftwareSerial.h>


int hrs1;
int hrs2;
int hrs3;
int mins1;
int mins2;
int mins3;
int qty;


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
hrs1=0;
hrs2=0;
hrs3=0;
mins1=0;
mins2=0;
mins3=0;
qty=0;

// put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

while(Serial.available())
{  rxdata = Serial.read();
  if(rxdata == '\r'||rxdata == '\n')
  {
    Serial.print(rxdata);
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

    hrs1 = string1.toInt();
    mins1 = string2.toInt();
    hrs2 = string3.toInt();
    mins2 = string4.toInt();
    hrs3 = string5.toInt();
    mins3 = string6.toInt();
    qty = string7.toInt();
    
    
    Serial.print("string1:");Serial.println(string1);
    Serial.print("string2:");Serial.println(string2);
    Serial.print("string3:");Serial.println(string3);
    Serial.print("string4:");Serial.println(string4);
    Serial.print("string5:");Serial.println(string5);
    Serial.print("string6:");Serial.println(string6);
    Serial.print("string7:");Serial.println(string7);
    
    Serial.print("hrs1:");Serial.println(hrs1);
    Serial.print("mins1:");Serial.println(mins1);
    Serial.print("hrs2:");Serial.println(hrs2);
    Serial.print("mins2:");Serial.println(mins2);
    Serial.print("hrs3:");Serial.println(hrs3);
    Serial.print("mins3:");Serial.println(mins3);
    Serial.print("qty:");Serial.println(qty);
    Serial.println();  
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
