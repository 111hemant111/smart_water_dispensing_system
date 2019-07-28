char tag[]= "FE0057CC3B5E";
char input[12];
int count = 0;
boolean flag =0;

void setup()
{
  Serial.begin(9600);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT); //WRONG
  }

void loop()
  {
    if (Serial.available())
      { //Serial.println("Test1");
        count=0;

        while(Serial.available()&&count<12) //RFID tag read into input
        {
          input[count]=Serial.read();
          count++;
          delay(5);
        }

        if(count==12)
        { //Serial.println("Test2");
          count=0;
          flag=1;

          while(count<12 && flag!=0)  //Check if read tag and authenticated tag are same
          { Serial.println(input);
            if (input[count]==tag[count])
              flag=1;
            else
              flag=0;
              //Serial.println("Test3");
              count++;              
          }
        }

        if (flag==1)  //Same
        {
          digitalWrite(12,HIGH);
          Serial.println("Access Allowed");
          delay(1000);
          digitalWrite(12,LOW);
        }

        else  //Different
        {
         digitalWrite(13,HIGH);
          Serial.println("Access Denied");
          delay(1000);
          digitalWrite(13,LOW); 
        }

        for (count=0;count<12;count++)  //Changing back input tag to FFFFFFFFFFFF
        {
          input[count]='F';
        }

        count=0;
      }
    }  
