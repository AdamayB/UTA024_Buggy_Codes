long previousMillisU = millis(); 
long intervalU = 500;  
#include<NewPing.h>
#include <NewPing.h>
#define trigPin 13
#define echoPin 12
#define MAX_DISTANCE 200
NewPing Sonar(trigPin,echoPin, MAX_DISTANCE);
int ir1 = A0;
int ir2 = A1;
int pin = 4;
int pin5 = 5;
int pin6 = 6;
int pin7 = 7;
int pin8 = 8;
int flag = 0;
int count = 0;
long st = millis(), endt;
unsigned value;
int l, r;
void setup() {
  // put your setup code here, to run once:
  pinMode(pin5, OUTPUT);
  pinMode(pin6, OUTPUT);
  pinMode(pin7, OUTPUT);
  pinMode(pin8, OUTPUT);
   
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(flag==0)
    {
      if (Serial.available()>0)
      {
        char s=Serial.read();
        switch (s)
        {
          case 'M':
          {
            flag=1;
          }
        }
      }
    }
    if (flag==1)
    {
      if (digitalRead(pin)>0)
      {
          value=pulseIn(pin,HIGH);
          if(value >1500 && value <2000)
          {
                Serial.println("Gantry 1 Crossed");
                stopp();
                delay(1000);
          }
          if(value >2500 && value <3000)
          {
           
                Serial.println("Gantry 2 Crossed");
                stopp();
                delay(1000);
          }
          if(value >500 && value <1000)
          {
                Serial.println("Gantry 3 Crossed");
                stopp();
                delay(1000);
          }
      }

unsigned long currentMillisU = millis();
 if(currentMillisU - previousMillisU > intervalU) 
       {
         
         previousMillisU = currentMillisU;  
         detectObstacle(); 
       }

    l = digitalRead(ir1);
    r = digitalRead(ir2);

    if (l == HIGH && r == HIGH)
    {
      forward();
    }

    else if (l == LOW && r == HIGH)
    {
      left();
    }

    else if (l == HIGH && r == LOW)
    {
      right();
    }
    else if (l == LOW && r==LOW)
    {
      forward();
      endt= millis();
     
      if(endt - st > 500)
      {
            count++;          
            st=millis();
      }     
            
      if(count == 1)
      {
          forward();
      }   
      if(count == 2)
      {
          left();
          
      }
      if(count == 3)
      {
          right();
          Serial.print(count);
      }
      if(count == 4)
      {
          left();

        Serial.print(count);
          delay(10);
      }                    
      if(count > 5)
      {
          stopp();
          delay(100000);
          Serial.print("Stop");  
          
      }     
    } 
}
}
void forward()
{
  digitalWrite(pin5, HIGH);
  digitalWrite(pin6, LOW);
  digitalWrite(pin7, LOW);
  digitalWrite(pin8, HIGH);
}
void left()
{
  digitalWrite(pin5, HIGH);
  digitalWrite(pin6, LOW);
  digitalWrite(pin7, LOW);
  digitalWrite(pin8, LOW);
}
void right()
{
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, LOW);
  digitalWrite(pin7, LOW);
  digitalWrite(pin8, HIGH);
}
void stopp()
{
  digitalWrite(pin5, LOW);
  digitalWrite(pin6, LOW);
  digitalWrite(pin7, LOW);
  digitalWrite(pin8, LOW);


}
void detectObstacle()
{
delay(50);
unsigned int distanceCm;
distanceCm = Sonar.ping_cm();
pinMode(echoPin,OUTPUT);
digitalWrite(echoPin,LOW);
pinMode(echoPin,INPUT);
//Serial.print("Ping: ");
//Serial.println(distanceCm);
//Serial.println("cm");
if((distanceCm<15) && (distanceCm>0))     
{
stopp();
delay(1000);
}
}
