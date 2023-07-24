#include <SoftwareSerial.h>
#include <virtuabotixRTC.h>
#include <L298N.h> 

SoftwareSerial sim(3, 2);
int _timeout;
String _buffer;
String number = "+917094472849"; //-->phone number

// Creation of the Real Time Clock Object
virtuabotixRTC myRTC(6, 7, 8);//6-->clk, 7-->data, 8-->reset



int hrs1;
int hrs2;
int hrs3;
int mins1;
int mins2;
int mins3;
int qty;
int limit1;
int limit2;

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


delay(7000); //delay for 7 seconds to make sure the modules get the signal
Serial.begin(9600);
_buffer.reserve(50);
Serial.println("System Started...");
sim.begin(9600);
delay(1000);
Serial.println("SIM ACTIVE");

pinMode(4,INPUT);
pinMode(5,INPUT);

pinMode(10,INPUT);                                        // analog Pin 10 as Input Pin for Motor A
analogWrite(10,200);
delay(2000);
Stop();                                                   // Function to Stop the Motor

// Set the current date, and time in the following format:
  // seconds, minutes, hours, day of the week, day of the month, month, year
  //myRTC.setDS1302Time(10, 19, 21, 3, 25, 5, 2022);
  
// put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
myRTC.updateTime();
Serial.print("Current Date / Time: ");
  Serial.print(myRTC.dayofmonth);
  Serial.print("/");
  Serial.print(myRTC.month);
  Serial.print("/");
  Serial.print(myRTC.year);
  Serial.print("  ");
  Serial.print(myRTC.hours);
  Serial.print(":");
  Serial.print(myRTC.minutes);
  Serial.print(":");
  Serial.println(myRTC.seconds);


if(digitalRead(4)==HIGH && limit1==1) //ir limit 1
{
  limit1=0;
}
if(digitalRead(5)==HIGH && limit2==1) //ir limit 1
{
  limit2=0;
}
if(digitalRead(4)==LOW && limit1==0) //ir limit 1
{
  SendMessage2();
  limit1=1;
}
if(digitalRead(5)==LOW && limit2==0) //ir limit 2
{
  
  SendMessage1();
  limit2=1;
}
if (myRTC.hours==hrs1 && myRTC.minutes==mins1 && myRTC.seconds==1)
{
  Run();
}
if (myRTC.hours==hrs2 && myRTC.minutes==mins2 && myRTC.seconds==1)
{
  Run();
}
if (myRTC.hours==hrs3 && myRTC.minutes==mins3 && myRTC.seconds==1)
{
  Run();
}
while(Serial.available())
{ Stop();
  
  

  
  rxdata = Serial.read();
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

    hrs1 = string1.toInt();
    mins1 = string2.toInt();
    hrs2 = string3.toInt();
    mins2 = string4.toInt();
    hrs3 = string5.toInt();
    mins3 = string6.toInt();
    qty = string7.toInt();
    
    Serial.print("hrs1:");Serial.println(hrs1);
    Serial.print("mins1:");Serial.println(mins1);
    Serial.print("hrs2:");Serial.println(hrs2);
    Serial.print("mins2:");Serial.println(mins2);
    Serial.print("hrs3:");Serial.println(hrs3);
    Serial.print("mins3:");Serial.println(mins3);
    Serial.print("qty:");Serial.println(qty);
    Serial.println();  

//rtc starts here


  // Start printing elements as individuals
 



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
if (sim.available() > 0)
    Serial.write(sim.read());
}

void SendMessage1()
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "The feed is below minimum level,\nplease refill container";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
}

void SendMessage2()
{
  //Serial.println ("Sending Message");
  sim.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  //Serial.println ("Set SMS Number");
  sim.println("AT+CMGS=\"" + number + "\"\r"); //Mobile phone number to send message
  delay(1000);
  String SMS = "The feed has reached critical level,\nrefill container immediately";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  _buffer = _readSerial();
}

String _readSerial() {
  _timeout = 0;
  while  (!sim.available() && _timeout < 12000  )
  {
    delay(13);
    _timeout++;
  }
  if (sim.available()) {
    return sim.readString();
  }
}

void Stop()
{
  analogWrite(10,0);                                // Pin 10 is Low
}

void Run()
{
if(qty <=5)
 {int i=0;
  while(i<qty)// number is second value
  {// Pin 10 is High for Motor A
    analogWrite(10,200);
    delay(1000);
    Serial.println(i);
    i=i+1;
   }
analogWrite(10,0);
delay(4000);
   }
   else
   {
    Stop();
   }
 
}
