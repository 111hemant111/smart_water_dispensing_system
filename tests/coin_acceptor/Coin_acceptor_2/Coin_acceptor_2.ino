const int coinInt = 0; 
//Attach coinInt to Interrupt Pin 0 (Digital Pin 2). Pin 3 = Interrpt Pin 1.

volatile float coinsValue = 0.00;
//Set the coinsValue to a Volatile float
//Volatile as this variable changes any time the Interrupt is triggered
int coinsChange = 0;                  
//A Coin has been inserted flag

void setup()
{
  Serial.begin(9600);                 
//Start Serial Communication
  attachInterrupt(coinInt, coinInserted, RISING);   
//If coinInt goes HIGH (a Pulse), call the coinInserted function
//An attachInterrupt will always trigger, even if your using delays
}

void coinInserted()    
//The function that is called every time it recieves a pulse
{
  coinsValue = coinsValue + 0.05;  
//As we set the Pulse to represent 5p or 5c we add this to the coinsValue
  coinsChange = 1;                           
//Flag that there has been a coin inserted
}

void loop()
{
  if(coinsChange == 1)          
//Check if a coin has been Inserted
  {
    coinsChange = 0;              
//unflag that a coin has been inserted
  
    Serial.print("Credit: £");
    Serial.println(coinsValue);    
//Print the Value of coins inserted
  }
}
