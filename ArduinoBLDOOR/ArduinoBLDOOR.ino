#include <SoftwareSerial.h>
#include <stdio.h>

//9 DOOR
//10 BUZZER
int doorONE = 9;
int doorTWO = 8;


int bluetoothTX = 11 ;
int bluetoothRX = 10 ;
char receivedValue ;

SoftwareSerial bluetooth ( bluetoothTX, bluetoothRX );

void setup()
{
  Serial.begin(9600);  
  Serial.println("console> ");
  
  pinMode(doorONE, OUTPUT);
  pinMode(doorTWO, OUTPUT);
 
  bluetooth.begin(115200);
  bluetooth.print("$$$");
  delay(100);
  bluetooth.println("U,9600,N");
  bluetooth.begin(9600);

}


void loop()
{
int power = 0;
int door = 0;
signed int data = 0;

 if( bluetooth.available() )
  {
    data = (int) bluetooth.read();
    Serial.println( data );                 // for debugging, show received data

      if(data == 26) 
      {
        allDown() ;
      }else if(data == 89)
      {
        allUp() ;
      }else{
        
      door = data / 100;                     // which door to select ?
      power = data % 100 ;             // 0 - 25 , DOOR power ( * 10 ) for actual value
           
    switch(door)                             // Now, let's select the right door.
    {
      
      case 0  : setDOORtwo ( power * 10 );  break;
      case 1  : setDOORone ( power * 10 );    break;
      default : setDOORtwo ( power * 10 );  break;       // DO NOT know what to do ? must be door 8
      
    }
      }

    bluetooth.flush();                       // IMPORTANT clean bluetooth stream, flush stuck data

  }

}


// SHUT DOWN all door
void allDown()
{
    digitalWrite(doorONE,  LOW ) ; 
      digitalWrite(doorTWO,  LOW ) ; 
}

// ALL up now :)

void allUp()
{
    digitalWrite(doorONE,  HIGH) ;  
     digitalWrite(doorTWO,  HIGH ) ; 
}


void setDOORone(int powerss)
{
 analogWrite(doorONE,  powerss ) ; 
}


void setDOORtwo(int powerss)
{
 analogWrite(doorTWO,  powerss ) ; 
}


