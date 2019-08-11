#include <LedControl.h>

int DIN = 7;
int CS =  6;
int CLK = 5;

byte neutral[8]= {0xe7,0xf7,0xf7,0xff,0xff,0xef,0xef,0xe7};
byte reverse[8] = {0xff,0xff,0xe7,0xfc,0xfc,0xe7,0xe7,0xe7};
byte one[8] = {0x1c,0x3c,0x1c,0x1c,0x1c,0x1c,0x1c,0x1c};
byte two[8]= {0x7e,0xff,0xe7,0xe,0x38,0xe0,0xff,0xff};
byte three[8]= {0xfe,0xff,0x7,0xff,0xff,0x7,0xff,0xfe};
byte four[8]= {0xee,0xee,0xee,0xff,0xff,0xe,0xe,0xe};
byte five[8] = {0xff,0xff,0xe0,0xff,0xff,0x7,0xff,0xff};
byte six[8] = {0xff,0xff,0xe0,0xff,0xff,0xe7,0xff,0xff};
byte seven[8] = {0xff,0xff,0xff,0x7,0x7,0x7,0x7,0x7};
byte eight[8] = {0x7e,0xff,0xe7,0xff,0xff,0xe7,0xff,0x7e};

LedControl lc=LedControl(DIN,CLK,CS,1);

void setup(){
  delay(2000);
  
  // Serial setup
 Serial.begin(9600);
 Serial.setTimeout(50);
  
 lc.shutdown(0,false);       
 lc.setIntensity(0,5);
 lc.clearDisplay(0);
}

String incoming;
unsigned long previousMillis = 0;
unsigned long currentMillis;

void loop()
{ 
  currentMillis = millis();
  // Turn off if no activity for 3s
  if (currentMillis - previousMillis >= 3000) {
    lc.clearDisplay(0);
  }
  
  if (Serial.available() > 0) {
    previousMillis = currentMillis; // reset
      incoming = Serial.readString();
      String gearString = getValue(incoming, ':', 1);
      int gear = gearString.toInt();

      Serial.println(gear);
      
      displayGear(gear);

  }   
}

void displayGear(int gear){
       switch(gear){

      case 0:
      printByte(neutral); 
      break;
        
      case 1:
      printByte(one); 
      break;

      case 2:
      printByte(two); 
      break; 

      case 3:
      printByte(three); 
      break;  

      case 4:
      printByte(four); 
      break;  

      case 5:
      printByte(five); 
      break;  

      case 6:
      printByte(six); 
      break;  

      case 7:
      printByte(seven); 
      break;  

      case 8:
      printByte(eight); 
      break; 

      case 10:
      printByte(reverse); 
      break; 
        
      }
  
}


void printByte(byte character [])
{
  int i = 0;
  for(i = 0; i < 8; i++)
  {
    lc.setRow( 0, i, character[i]);
  }
}

String getValue(String data, char separator, int index)
{
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i = 0; i <= maxIndex && found <= index; i++){
    if(data.charAt(i) == separator || i == maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
