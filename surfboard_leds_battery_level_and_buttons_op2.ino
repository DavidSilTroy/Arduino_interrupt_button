#include <Servo.h>
Servo esc_signal;

int option  = 0;  //this is to know witch button was touched
int count   = 0;  //this is to know how much time the output will be working

int btn100  = 8;  //for pin 8
int btn75   = 7;  //for pin 7
int btn50   = 12; //for pin 12
int btn25   = 13; //for pin 13

int greenLed  = 11; //for pin 11
int yellowLed = 10; //for pin 10
int redLed    = 9;  //for pin 9

int highLevel = 750; //number to compare with the analog reader
int lowLevel  = 300; //number to compare with the analog reader

int output_signal   = 0; //for output value, this goes between 0 and 255 to the pwd

void setup() {
  pinMode(2,INPUT);//this button stop the process
  
  pinMode(btn100,INPUT);//  100% power for 8s and 75% power for 60s
  pinMode(btn75,INPUT);//   75% power for 100s
  pinMode(btn50,INPUT);//   50% power for 100s
  pinMode(btn25,INPUT);//   25% power for 100s

  pinMode(greenLed,OUTPUT);//   to turn on the green Led     
  pinMode(yellowLed,OUTPUT);//  to turn on the yellow Led 
  pinMode(redLed,OUTPUT);//     to turn on the red Led
  
  
  attachInterrupt(digitalPinToInterrupt(2),BotonStop,RISING); //this button will work even if something else is in process

  Serial.begin(9600); //to print the values

  esc_signal.attach(6);  //Specify here the pin number on which the signal pin of ESC is connected.
  esc_signal.write(30);   //ESC arm command. ESCs won't start unless input speed is less during initialization.
  delay(3000);            //ESC initialization delay.
  
}

void loop() {
  
  if(digitalRead(btn100)){
    output_signal=map(100,0,100,40,130);
    option=1;
    Power100();
    }
  if(digitalRead(btn75)){
    output_signal=map(75,0,100,40,130);
    option=2;
    Power75();
    }
  if(digitalRead(btn50)){
    output_signal=map(50,0,100,40,130);
    option=3;
    Power50();
    }
  if(digitalRead(btn25)){
    output_signal=map(25,0,100,40,130);
    option=4;
    Power25();
    }
    
  CheckOption();
  CheckBattery(analogRead(A1));
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
   Serial.println(A1);
   if(A1>=highLevel){
    digitalWrite(redLed,HIGH);
    digitalWrite(yellowLed,HIGH);
    digitalWrite(greenLed,HIGH);
    }
    if(A1<=highLevel&&A1>=lowLevel){
    digitalWrite(redLed,HIGH);
    digitalWrite(yellowLed,HIGH);
    digitalWrite(greenLed,LOW);
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
void Power75(){
  esc_signal.write(output_signal);
  }
void Power50(){
  esc_signal.write(output_signal);
  }
void Power25(){
  esc_signal.write(output_signal);
  }
  
void CheckOption(){
  switch (option) {
  case 1:
    if(count==80){
      output_signal=map(75,0,100,40,130                                                                                                                                                                                                                                                                                     );
      Power75();
      }
    if(count>=680){
      BotonStop();
      }
    break;
  case 2:
    if(count>=1000){
      BotonStop();
      }
      break;
  case 3:
    if(count>=1000){
      BotonStop();
      }
    break;
  case 4:
    if(count>=1000){
      BotonStop();
      }
    break;
  default:
    BotonStop();
    break;
}
  }
