#include <IRremote.h>

const int ENA = 5;
const int ENB = 10;
const int In1 = 6;              
const int In2 = 7;
const int In3 = 8;
const int In4 = 9;

int irReceiver = 2;
IRrecv irrecv(irReceiver);
decode_results results;

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(In1, OUTPUT);
  pinMode(In2, OUTPUT);
  pinMode(In3, OUTPUT);
  pinMode(In4, OUTPUT);
}

void IRaction(int IRcode)
{
     switch(IRcode)
     {
       case 0xFF629D: 
         Goahead(); 
         break;
       case 0xFFA857: 
         Goback(); 
         break;
       case 0xFF22DD: 
         Goleft();  
         break;
       case 0xFFC23D: 
         Goright(); 
         break;
       case 0xFF02FD: 
         Carstop(); 
         break;
     }
}

void Goahead(){
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);
  digitalWrite(In3,HIGH);
  digitalWrite(In4,LOW);
  
  analogWrite(ENA,200);
  analogWrite(ENB,200);
}

void Goback(){
  digitalWrite(In1,LOW);
  digitalWrite(In2,HIGH);
  digitalWrite(In3,LOW);
  digitalWrite(In4,HIGH);
  
  analogWrite(ENA,200);
  analogWrite(ENB,200);
}

void Goleft(){
  digitalWrite(In1,LOW);
  digitalWrite(In2,LOW);
  digitalWrite(In3,HIGH);
  digitalWrite(In4,LOW);
  
  analogWrite(ENA,200);
  analogWrite(ENB,200);
}

void Goright(){
  digitalWrite(In1,HIGH);
  digitalWrite(In2,LOW);
  digitalWrite(In3,LOW);
  digitalWrite(In4,LOW);
  
  analogWrite(ENA,200);
  analogWrite(ENB,200);
}

void Carstop(){
  digitalWrite(In1,LOW);
  digitalWrite(In2,LOW);
  digitalWrite(In3,LOW);
  digitalWrite(In4,LOW);
  
  analogWrite(ENA,0);
  analogWrite(ENB,0);
}

void loop()
{
  Goahead();
  delay(1000);
  Goback();
  delay(1000);
  Goleft();
  delay(1000);
  Goright();
  delay(1000);
  Carstop();
  delay(5000);
}






