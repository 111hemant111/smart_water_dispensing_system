#include "Arduino.h"
#include <EDB.h>
#include <SD.h>
 
File dbFile;
 
#define TABLE_SIZE 1024
#define RECORDS_TO_CREATE 20
 
struct LogEvent {
  int id;
  int balance;
} 
logEvent;
 
void writer(unsigned long address, byte data)
{
  dbFile.seek(address); 
  dbFile.write(data);
  dbFile.flush();
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
   
  Serial.println("Opening water.txt ...");
  dbFile = SD.open("water.txt", FILE_WRITE);
   
  db.create(0, TABLE_SIZE, sizeof(logEvent));
   
  Serial.print("Record Count: "); Serial.println(db.count());
 
  Serial.println("Creating Records...");
  int recno;
  for (recno = 1; recno <= RECORDS_TO_CREATE; recno++)
  {
    logEvent.id = recno; 
    logEvent.balance = recno * 2;
    db.appendRec(EDB_REC logEvent);
  }
   
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
