
/////*******************Smart water dispensing system for KMC******************/////
/////**********************Developed by Hemant and Girish**********************/////

#include<LiquidCrystal.h>
char input[12];
int count = 0;
boolean flag =0;
int total=10;

/////*****Water flow sensor*****/////
float calibrationFactor = 4.5;
byte sensorInterrupt = 0;
volatile byte pulseCount;
float flowml;
float totalml;
unsigned long oldTime;

/////*****Struct*****/////
struct database {
  String id;
  int balance;
} ;

struct database cus[10];

/////*****LCD initialisation*****/////

LiquidCrystal lcd1(8,7,6,5,4,3);
//LiquidCrystal lcd2(27,26,25,24,23,22);

void setup()
{ 
  Serial.begin(38400);
  lcd1.begin(16,2);
  
  pinMode(11,OUTPUT); /*****Buzzer pin*****/
  pinMode(12,OUTPUT); /*****Correct LED*****/
  pinMode(13,OUTPUT); /*****Wrong LED*****/
  pinMode(2,INPUT);  /*****Water flow sensor*****/
  pinMode(10,OUTPUT); /*****Water switch relay*****/
  digitalWrite(2, HIGH);  /*****HIGH to water flow sensor*****/

  /////*****Water flow initialisation*****/////
  pulseCount = 0;
  flowml     = 0.0;
  totalml    = 0.0;
  oldTime    = 0;
  
  cus[0].id="180089177EF8";
  cus[0].balance=2;
  cus[1].id="1800893D02AE";
  cus[1].balance=6;

  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
}

void loop() {

    /////*****RFID tag read into input*****/////
    if (Serial.available())
      { Serial.println("Test1");
        count=0;

        while(Serial.available()&&count<12) 
        {
          input[count]=Serial.read();
          count++;
          delay(5);
        }

        if(count==12)
        { Serial.println("Test2");
          count=0;
          flag=1;
        }
      }
      
      /////*****Check the input tag in the database*****/////
      
      int curlog;
      int check=0;
      for (curlog=0;curlog<total;curlog++)
      {
        for (count=0;count<12;count++)
        {
          if (cus[curlog].id[count]==input[count])
            check++;
            Serial.println("Test3");
        }

        if (check==12)
          { 
            flag=2;
            if (cus[curlog].balance>4)
            {
            digitalWrite(12,HIGH);
            flag=3;
            Serial.println("Test4");
            goto found;
            }
          }
      }

      found: ;    
       
      /////*****Setting the input array to FFFFFFFFFFFF******/////
      
        for (count=0;count<12;count++)  //Changing back input tag to FFFFFFFFFFFF
        {
          input[count]='F';
        }
        count=0;

      /////*****LCD and buzzer part*****/////
      
      if (flag==1)
      {
        /*Invalid card*/;
        Serial.println("Test5");
        lcd1.setCursor(0,0);
        lcd1.print(" Invalid card ");
        tone(11,2000,1000);
        delay(500);
        noTone(11);
        delay(500);
        tone(11,2000,1000);
        delay(500);
        noTone(11);
      }
      else if (flag==2)
      {
        /*Low balance, please recharge*/;
        
        lcd1.setCursor(0,0);
        lcd1.print("Low balance");
        lcd1.setCursor(0,1);
        lcd1.print("Please recharge");
        Serial.println("Test6");
        tone(11,2000,1000);
        delay(500);
        noTone(11);
        delay(500);
        tone(11,2000,1000);
        delay(500);
        noTone(11);
      }
      else if (flag==3)
      {
        /*Please place the can*/;
        Serial.println("Test7");
        tone(11,2000,1000);
        delay(2000);
        noTone(11);
        digitalWrite(10,HIGH);
        /*****Water flow sensor*****/
        for (;totalml<100;)
        {
        if ((millis() - oldTime)>1000)
           {
            detachInterrupt(sensorInterrupt);
            flowml = ((((1000.0/(millis()-oldTime))*pulseCount)/calibrationFactor)/60)*1000;
            oldTime = millis();
            totalml+=flowml;

            if(totalml>100)
              digitalWrite(10,LOW);
           }
            
        }
      }             
}

void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
