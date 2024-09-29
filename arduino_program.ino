#include <HCSR04.h>
int speed=140; //255
const int trigPin = 3;
const int echoPin = 4;
HCSR04 hc(3, 4); //initialisation class HCSR04 (trig pin , echo pin)
float duration, distance;
const int PIR_PIN = 2;
int warm_up;
int pir_output;

void setup() {
  Serial.begin(9600);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT); 
  pinMode(10, OUTPUT);  
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);  
  pinMode(5, OUTPUT);  
  pinMode(6, OUTPUT); 
  analogWrite(5,speed);
  analogWrite(6,speed);
  pinMode(PIR_PIN, INPUT);
  Serial.println("Configuring sensor..please wait.");
  delay(5000);
}

void loop() { 
  
  pir_output = digitalRead(PIR_PIN);
  int ultrasonic_distance=hc.dist();  
  if(pir_output == LOW )
  {
    if( warm_up == 1 )
     {
      Serial.println("setting back PIR Up");
      warm_up = 0;
      delay(2000);
    }
    Serial.println("No object in sight");
    digitalWrite(12,LOW);
    delay(200);
  }
  else
  {
    Serial.print("Object detected\n"); 
    digitalWrite(12,HIGH);   
    warm_up = 1;
    delay(1000);
  }    
  Serial.print("Distance: "); 
  Serial.print(ultrasonic_distance);  
  Serial.println("cm");

  if(ultrasonic_distance<=20){
    stop();
  }
  if(pir_output == HIGH){
    stop();
  }
  delay(200);

    if (Serial.available() > 0) {           
    char dat = Serial.read();
    if(dat=='1'){
      forward();
    }
    else if(dat=='2'){
      backward();
    }
    else if(dat=='3'){
      left();
    }
    else if(dat=='4'){
      right();
    }
    else if(dat=='5'){
      stop();
    }
    else{      
    }
  }
}

void forward() {
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH); 
  Serial.println("Moving Forward"); 
}
void backward() {
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW); 
  Serial.println("Moving Backward");  
}
void left() {
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);  
  Serial.println("Moving Left"); 
}
void right() {
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);  
  Serial.println("Moving Right"); 
}
void stop() {
  digitalWrite(8,LOW);
  digitalWrite(9,LOW);
  digitalWrite(10,LOW);
  digitalWrite(11,LOW);
  Serial.println("Stop Robot"); 
}
