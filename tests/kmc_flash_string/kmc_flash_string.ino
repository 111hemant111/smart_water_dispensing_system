struct LogEvent {
  char *id;
  int balance;
} ;

int i;

void setup()
{
  cus[2000] *createCus(char *id, int balance){
    cus[2000] *p = malloc(sizeof(struct cus[2000]));
    p->id=strdup(id);
    p->balance=balance;
    return p;
    
  }
  //struct LogEvent *cus[2000];
  //cus[2000]= (struct LogEvent *) malloc (sizeof(struct LogEvent));
  Serial.begin(9600);

  for (i=0;i<40;i++)
  {
    *cus[i].id="2354bc2354bc";
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
