
/////*******************Smart water dispensing system for KMC******************/////
/////**********************Developed by Hemant and Girish**********************/////

#include<LiquidCrystal.h>
char input[12];
String compare;
char checkstr[12];
int count = 0;
int flag =0;
int total=2;
int a;
char master[]= "FE0057C1761E";
int trig=1;

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
  Serial.begin(9600);
  lcd1.begin(16,2);
  
  pinMode(11,OUTPUT); /*****Buzzer pin*****/
  pinMode(12,OUTPUT); /*****Correct LED*****/
  pinMode(13,OUTPUT); /*****Wrong LED*****/
  pinMode(10,OUTPUT); /*****Water switch relay*****/
  pinMode(2,INPUT);  /*****Water flow sensor*****/
  digitalWrite(2, HIGH);  /*****HIGH to water flow sensor*****/

  /////*****Water flow initialisation*****/////
  pulseCount = 0;
  flowml     = 0.0;
  totalml    = 0.0;
  oldTime    = 0;
  
  cus[0].id=String("180089177EF8");
  cus[0].balance=2;
  cus[1].id=String("1800893D02AE");
  cus[1].balance=6;

}

void loop() {
  lcd1.setCursor(0,0);
  lcd1.print("   Welcome to   ");
  lcd1.setCursor(0,1);
  lcd1.print("      KMC       ");
  start:
  digitalWrite(12,LOW);
  digitalWrite(13,LOW);

    /////*****RFID tag read into input*****/////
    if (Serial.available())
      { Serial.println("Test1");
        count=0;

        while(Serial.available()&&count<12) 
        {
          input[count]=Serial.read();
          Serial.print(input[count]);
          count++;
          delay(5);
        }

        if(count==12)
        { Serial.println("Test2");
          count=0;
          flag=1;
        }

        /////*****Master card check*****/////
        Serial.println(Serial.available());
        Serial.println(strncmp(input,master,12));
    
        lcd1.clear();
        for (;!strncmp(input,master,12)&&trig==1;)
        {
          digitalWrite(10,HIGH);
          lcd1.setCursor(0,0);
          lcd1.print("   Master card ");
          digitalWrite(11,HIGH);
          if (Serial.available())
          {
            count=0;
            while(Serial.available()&&count<12) 
              {
                input[count]=Serial.read();
                count++;
                delay(5);
              }
            if (!strncmp(input,master,12))
              trig=0;
          }
        }
          trig=1;
          digitalWrite(10,LOW);
          digitalWrite(11,LOW);
          lcd1.clear();

       if (!strncmp(input,master,12))
           goto start;
      //delay(5);
      //Serial.println(input);
      
      /////*****Check the input tag in the database*****/////
      
      int curlog;
      int check=0;
      for (curlog=0;curlog<total;curlog++)
      {//Serial.print(cus[curlog].id);
        count=0;

      for(a=0;a<12;a++)
      {
        checkstr[a]=cus[curlog].id[a];
      }
      
      //Serial.print(checkstr);
      //Serial.print(input);
      for(a=0;a<12;a++)
      {
        if(input[a]==checkstr[a])
          count++;
      }
      //Serial.println(count);
      //Serial.println(checkstr);
      delay(5);
        if (count==12)
        {
          
          Serial.println("Test3");
          delay(50);
          flag=2;
          if (cus[curlog].balance>4)
          {
            digitalWrite(12,HIGH);
            flag=3;
            Serial.println(flag);
            Serial.println("Test4");
            goto found;
          }
        }

      }

      found: ;   
      //Serial.println(flag); 
       
      /////*****Setting the input array to FFFFFFFFFFFF******/////
      
        for (count=0;count<12;count++)  //Changing back input tag to FFFFFFFFFFFF
        {
          input[count]='F';
        }
        count=0;

      /////*****LCD and buzzer part*****/////
      
      if (flag==1)
      { lcd1.clear();
        /*Invalid card*/;
        Serial.println("Test5");
        digitalWrite(13,HIGH);
        lcd1.setCursor(0,0);
        lcd1.print("  Invalid card  ");
        tone(11,2000,1000);
        delay(500);
        noTone(11);
        delay(500);
        tone(11,2000,1000);
        delay(500);
        noTone(11);
      }
      else if (flag==2)
      { lcd1.clear();
        /*Low balance, please recharge*/;
        digitalWrite(13,HIGH);
        lcd1.setCursor(0,0);
        lcd1.print("   Low balance  ");
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
        lcd1.clear();
        lcd1.setCursor(0,0);
        lcd1.print("  Please place  ");
        lcd1.setCursor(0,1);
        lcd1.print("    the can    ");
        /*Please place the can*/;
        Serial.println("Test7");
        tone(11,2000,1000);
        delay(2000);
        noTone(11);
        digitalWrite(10,HIGH);
        delay(5000);
        digitalWrite(10,LOW);
            
        }
      }
                 
}

