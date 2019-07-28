struct LogEvent {
  int id;
  int balance;
} ;

int i;

void setup()
{
  struct LogEvent cus[2000];
  Serial.begin(9600);

  for (i=0;i<40;i++)
  {
    cus[i].id=i;
    cus[i].balance=50*i;
  }
   
  for(i=0;i<40;i++)
  {
    Serial.println(cus[i].id);
    Serial.println(cus[i].balance);
  }
}
 
void loop()
{  
}
