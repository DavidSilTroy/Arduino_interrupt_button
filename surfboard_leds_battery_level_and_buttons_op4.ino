#include <Servo.h>
Servo esc_signal;

int option  = 0;  //this is to know witch button was touched
int count   = 0;  //this is to know how much time the output will be working

int btn100  = 7; //for pin 7
int btn85   = 6; //for pin 6
int btn75   = 5; //for pin 5
int btn50   = 4; //for pin 4

int pinEsc = 11; //for pin 11

int greenLed  = 8; //for pin 8
int yellowLed = 9; //for pin 9
int redLed    = 10;//for pin 10

//750-900
int highLevel   = 850;//number to compare with the analog reader
int mediumLevel = 800;//number to compare with the analog reader
int lowLevel    = 750;//number to compare with the analog reader

int output_signal   = 0; //for output value, this goes between 0 and 255 to the pwd

void setup() {
  pinMode(2,INPUT);//this button stop the process
  
  pinMode(btn100,INPUT);//  100% power for 8s and 75% power for 60s
  pinMode(btn85,INPUT);//   85% power for 100s
  pinMode(btn75,INPUT);//   75% power for 100s
  pinMode(btn50,INPUT);//   50% power for 100s

  pinMode(greenLed,OUTPUT);//   to turn on the green Led     
  pinMode(yellowLed,OUTPUT);//  to turn on the yellow Led 
  pinMode(redLed,OUTPUT);//     to turn on the red Led
  
  
  attachInterrupt(digitalPinToInterrupt(2),BotonStop,RISING); //this button will work even if something else is in process

  Serial.begin(9600); //to print the values

  esc_signal.attach(pinEsc);  //Specify here the pin number on which the signal pin of ESC is connected.
  esc_signal.write(30);   //ESC arm command. ESCs won't start unless input speed is less during initialization.
  delay(3000);            //ESC initialization delay.
  
}

void loop() {
  
  if(digitalRead(btn100)){
    output_signal=map(100,0,100,40,130);
    Serial.print("100 Signal");
    Serial.println(output_signal);
    option=1;
    Power100();
    }
  if(digitalRead(btn85)){
    output_signal=map(85,0,100,40,130);
    Serial.print("75 Signal");
    Serial.println(output_signal);
    option=2;
    Power85();
    }
  if(digitalRead(btn75)){
    output_signal=map(75,0,100,40,130);
    Serial.print("50 Signal");
    Serial.println(output_signal);
    option=3;
    Power75();
    }
  if(digitalRead(btn50)){
    output_signal=map(50,0,100,40,130);
    Serial.print("25 Signal");
    Serial.println(output_signal);
    option=4;
    Power50();
    }
    
  CheckOption();
  //Serial.print("A1:");
  CheckBattery(analogRead(A1));
  if(analogRead(A1)>1){
    //Serial.print("A1:");
    //Serial.println(analogRead(A1));
    //Serial.println(" ");
  }
  //Serial.println(" ");
  count+=1;
  delay(100);
  
}

void BotonStop(){
//pin2 button
  option=0;
  count=0;
  esc_signal.write(30);
}

void CheckBattery(int A1){
   //Serial.println(A1);
    
    if(A1>=mediumLevel){
    digitalWrite(yellowLed,HIGH);
    digitalWrite(redLed,HIGH);
    digitalWrite(greenLed,LOW);
    }
    if(A1>=highLevel){
    digitalWrite(greenLed,HIGH);
    digitalWrite(redLed,HIGH);
    digitalWrite(yellowLed,HIGH);
    }
    if(A1<=lowLevel){
    digitalWrite(redLed,HIGH);
    digitalWrite(yellowLed,LOW);
    digitalWrite(greenLed,LOW);
    }
  }

void Power100(){
  esc_signal.write(output_signal);
  }
void Power85(){
  esc_signal.write(output_signal);
  }
void Power75(){
  esc_signal.write(output_signal);
  }
void Power50(){
  esc_signal.write(output_signal);
  }
  
void CheckOption(){
  switch (option) {
  case 1:
    Serial.println("100%");
    if(count==80){
      output_signal=map(85,0,100,40,130);
      Power75();
      }
    if(count>=680){
      BotonStop();
      }
    break;
  case 2:
    Serial.println("75%");
    if(count>=1000){
      BotonStop();
      }
      break;
  case 3:
    Serial.println("50%");
    if(count>=1000){
      BotonStop();
      }
    break;
  case 4:
    Serial.println("25%");
    if(count>=1000){
      BotonStop();
      }
    break;
  default:
    //Serial.println("0%");
    BotonStop();
    break;
}
  }
