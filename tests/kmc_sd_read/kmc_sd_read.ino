#include "Arduino.h"
#include <EDB.h>
#include <SD.h>
 
File dbFile;
 
#define TABLE_SIZE 512
#define RECORDS_TO_CREATE 10
 
struct LogEvent {
  int id;
  int balance;
} 
logEvent;
 
void writer(unsigned long address, byte data)
{
  dbFile.seek(address); 
  dbFile.write(data);
}
 
byte reader(unsigned long address)
{
  dbFile.seek(address); 
  return dbFile.read(); 
}
 
 
EDB db(&writer, &reader);
 
void setup()
{
  Serial.begin(9600);
    
  Serial.print("Initializing SD card...");
   
  pinMode(10, OUTPUT);
   
  if (!SD.begin()) {
    Serial.println("Initialization failed!");
    return;
  }
   
  Serial.println("Initialization done.");
   
  Serial.println("Opening water.db ...");
  dbFile = SD.open("water.txt", FILE_READ);
   
  //db.create(0, TABLE_SIZE, sizeof(logEvent));
   
  Serial.print("Record Count: "); Serial.println(db.count());
 
  int recno;
  
  Serial.print("Record Count: "); Serial.println(db.count());
  for (recno = 1; recno < RECORDS_TO_CREATE; recno++)
  {
    db.readRec(recno, EDB_REC logEvent);
    Serial.print("ID: "); Serial.println(logEvent.id);
    Serial.print("Balance: "); Serial.println(logEvent.balance);   
  }
}
 
 
void loop()
{
  
}
