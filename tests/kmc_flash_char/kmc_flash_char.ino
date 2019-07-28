struct LogEvent {
  char id[12];
  int balance;
} ;

int i;

int total=10;
void setup()
{
  struct LogEvent cus[100];
  Serial.begin(9600);
   
  for(i=0;i<40;i++)
  {
    Serial.println(cus[i].id);
    Serial.println(cus[i].balance);
  }

  for (i=0;i<12;i++)
      {
        cus[total+1].id[i]=input[i];
      }
}
 
void loop()
{  
  
}
