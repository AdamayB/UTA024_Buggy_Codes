const int tp = 13;
const int ep = 12;
long duration ;
int distance ;

int counter = 0;
unsigned long int st =0 ,ft =0,gST =0,gFT = 0;
int pin=4;
unsigned valueOfSignalGantry ;
////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(tp,OUTPUT);
  pinMode(ep,INPUT);
  pinMode(A1,INPUT);//l
  pinMode(A2,INPUT);//r
  pinMode(pin,INPUT);
  Serial.begin(9600);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////
// BUGGY MOVEMENT
void forward() {
//digitalWrite(5,HIGH);
analogWrite(5,180);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
//digitalWrite(8,HIGH);
analogWrite(8,180);
}
void backward() {
digitalWrite(5,LOW);
digitalWrite(6,HIGH);
digitalWrite(7,HIGH);
digitalWrite(8,LOW);
}
void right() {
digitalWrite(5,LOW);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,HIGH);
}
void left() {
digitalWrite(5,HIGH);
digitalWrite(6,LOW);
digitalWrite(7,LOW);
digitalWrite(8,LOW);
}
void stopf() {
digitalWrite(5, LOW);
digitalWrite (6, LOW);
digitalWrite (7, LOW);
digitalWrite (8, LOW);
}
void clockwise(){
digitalWrite(5,LOW);
digitalWrite(6,HIGH);
digitalWrite(7,LOW);
digitalWrite(8,HIGH);
}
//////////////////////////////////////////////////////////////////////////////////////////////////
// GANTRY SIGNAL  
void checkGantry(){
//    now check for different gantry signals
  valueOfSignalGantry=pulseIn(pin,HIGH,3000);
    if (valueOfSignalGantry >400 && valueOfSignalGantry<1000){
      Serial.println(valueOfSignalGantry);
      Serial.println("Gantry 1 ");
      stopf();
      delay(1000);
      forward();
      delay(400);
    }
//    more else if conditions    
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////
// LINE FOLLOWING CODE
void buggy(){
  int l,r;
  digitalWrite(tp,LOW);
  delayMicroseconds(2);
  digitalWrite(tp,HIGH);
  delayMicroseconds(10);
  digitalWrite(tp,LOW);
  duration = pulseIn(ep,HIGH,5000);
 
  distance = (duration * 0.034)/2;
//  Serial.println(distance);
  
  
  if (distance <= 15 && distance>0){
    stopf();
  }
  else{ 
   l= digitalRead(A1);
   r= digitalRead(A2);
   checkGantry();

  if(l==1 && r== 0){
     right();
  }
  else if(l==0 && r==1){
   
    left();
  }
  else if(l ==1 && r== 1){
    forward();
  }
  else if(l == 0 && r== 0){
    st = millis();
    if(st - 500 > ft){
      counter++;
      Serial.print("value of counter :");
      Serial.println(counter);
      ft = millis();
    }
    if(counter ==1){
      forward();
    }
    else if(counter == 2){
      right();  
    }
    else if(counter == 3){
      left();
    }
    //delay kei bad ek bari aur detect kar rahi thi
    else if(counter == 4){
      //      right();
      clockwise();
      delay(50);
      stopf();
      delay(10);  
    }
    else if(counter == 6){
      stopf();
//      exit(0);
      delay(5000);
      counter=0;  
    }
  }
   
  }
}
char s;
void loop(){
  if (Serial.available()>0){
    char temp = Serial.read();
    if (temp == 'G' || temp == 'S'){
      s = temp;
    }
//  s = Serial.read();
}
if ( s == 'G'){ 
  buggy();
}
else if( s== 'S'){
  stopf();
  delay(1000);
}

}
