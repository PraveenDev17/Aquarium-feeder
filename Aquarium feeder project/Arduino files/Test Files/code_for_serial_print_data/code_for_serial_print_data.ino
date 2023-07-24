#include <L298N.h>                                  // Library for L298N Motor Driver Module

 

int val;                                                        // Initialize Variable

int nb;                                                         // Initialize Variable

int vSpeed;

int shiftspeed;

int buzzer  = 4;

int light1  = 12;

int light2  = 11;

/* The setup() function is called when a sketch starts. It is used to initialize variables, pin modes, start using libraries, etc. This function will only run once, after each power up or reset of the Arduino board. */

 

void setup()

{

 

Serial.begin(9600);                                           // Baud Rate for Serial Communication

pinMode(10,INPUT);                                        // analog Pin 10 as Input Pin for Motor A

pinMode(9,INPUT);                                          // analog Pin 9 as Input Pin for Motor A

pinMode(6,INPUT);                                          // analog Pin 6 as Input Pin for Motor B

pinMode(5,INPUT);                                          // analog Pin 5 as Input Pin for Motor B

pinMode(light1, OUTPUT); 
    
pinMode(light2, OUTPUT);

 

}
 

/* This Particular Function is used for Repeated Execution of the Circuit until Specified. */

 

/* analogWrite is used to write a vSpeed or a 0 value to a analog pin (0 is the voltage level) */

 

void loop()

{

if(Serial.available()>0)                                 // Check if Data is available

{

String data= Serial.readString();    
Serial.print(data);// Read the Data

Stop();                                                       
  if(data == '0')
     {vSpeed = 0;}
    if(data == '1')
     {vSpeed = 120;}
    if(data == '2')
     {vSpeed = 140;}
    if(data == '3')
     {vSpeed = 160;}
    if(data == '4')
     {vSpeed = 180;}
    if(data == '5')
     {vSpeed = 200;}
    if(data == '6')
     {vSpeed = 210;}
    if(data == '7')
     {vSpeed = 220;}
    if(data == '8')
     {vSpeed = 230;}
    if(data == '9')
     {vSpeed = 240;}
    if(data == 'q')
     {vSpeed = 255;}

     {shiftspeed = (80/100)*vSpeed;}

  if(data=='R')                                               // For Right Movement

  {

    analogWrite(10,vSpeed);                             // Pin 10 is High for Motor A

    analogWrite(9,0);                                // Pin 9 is Low

    analogWrite(5,vSpeed);                               // Pin 5 is High for Motor B

    analogWrite(6,0);                                // Pin 6 is Low

    }

    else if(data=='L')                                      // For Left Movement

    {

    analogWrite(10,0);                              // Pin 10 is Low

    analogWrite(9,vSpeed);                               // Pin 9 is High for Motor A

    analogWrite(5,0);                                // Pin 5 is Low

    analogWrite(6,vSpeed);                               // Pin 6 is High for Motor B

     

    }

      else if(data=='F')                                      // For Forward Movement

      {

        analogWrite(10,0);                           // Pin 10 is Low

        analogWrite(9,vSpeed);                            // Pin 9 is High for Motor A

        analogWrite(5,vSpeed);                            // Pin 5 is High for Motor B

        analogWrite(6,0);                             // Pin 6 is Low

      }

    else if(data=='B')                                      // For Backward Movement      

    {

      analogWrite(10,vSpeed);                           // Pin 10 is High for Motor A

      analogWrite(9,0);                              // Pin 9 is Low

      analogWrite(5,0);                              // Pin 5 is Low

      analogWrite(6,vSpeed);                             // Pin 6 is High for Motor B

    } 

 //If data is equal with number 'I', car will go forward right
    else if (data == 'I')
    
    {
      analogWrite(10, 0); 
      
      analogWrite(9, vSpeed); 
      
      analogWrite(5, shiftspeed);     
      
      analogWrite(6, 0);

    }

    //If data is equal with number 'G', car will go forward left
    else if (data == 'G') {
      analogWrite(10, 0);
      
      analogWrite(9, shiftspeed);  
      
      analogWrite(5, vSpeed);
      
      analogWrite(6, 0);

    }
    
     //If data is equal with number 'J', car will go backward right
    else if (data == 'J') {
      analogWrite(10, shiftspeed);
      
      analogWrite(9, 0); 
      
      analogWrite(5, 0); 
      
      analogWrite(6, vSpeed);

    }

    //If data is equal with number 'H', car will go backward left
    else if (data == 'H') {
      analogWrite(10, vSpeed );
      
      analogWrite(9, 0); 
      
      analogWrite(5, 0);
      
      analogWrite(6, shiftspeed);

    }
    
    
    //If data is equal with letter 'N', buzzer turn on
    if (data == 'V') {
      tone(buzzer, 500); 
    }
    if (data == 'v') {
      noTone(buzzer); 
    }

    if (data == "Success") {
      digitalWrite(light1, HIGH); 
    }
    if (data == 'w') {
      digitalWrite(light1, LOW); 
    }
    
  /***************************light2*****************************/
  //If data is equal with letter 'U', light2 turn on
    if (data == 'U') {
      digitalWrite(light2, HIGH); 
    }
    if (data == 'u') {
      digitalWrite(light2, LOW); 
    }


 

}

 

}

void Stop()                                                   // Function to Stop the Motor

{

  analogWrite(10,0);                                // Pin 10 is Low

  analogWrite(9,0);                                  // Pin 9 is Low

  analogWrite(5,0);                                  // Pin 5 is Low

  analogWrite(6,0);                                  // Pin 6 is Low

 

 }
