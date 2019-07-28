#include "Arduino.h"
#include <EDB.h>
#include <SD.h>


File dbFile;

void setup()
{
Serial.begin(9600);

dbFile.seek(2000);
dbFile.write(12);
dbFile.flush();

dbFile = SD.open("water.txt", FILE_WRITE);
dbFile.seek(2000);
Serial.println(dbFile.read());
}

void loop()
{}
