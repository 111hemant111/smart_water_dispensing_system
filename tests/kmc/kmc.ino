  int count = 0;
void setup()
{
  Serial.begin(9600);
}
void loop()
{
  if(Serial.available())
  {
    {
      char input = Serial.read();
      Serial.print(input);
      count++; //
      delay(5); //
    }
   
  }

  
  if (count==12)
  {
      Serial.println("");
      count=0;
  }
 
}
