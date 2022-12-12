#include <Servo.h>
Servo esc_signal;

int option  = 0;  //this is to know witch button was touched
int count   = 0;  //this is to know how much time the output will be working

int pinEsc = 11; //for pin 11

int greenLed  = 8; //for pin 8
int yellowLed = 9; //for pin 9
int redLed    = 10;//for pin 10

int btn1  = 7; //for pin 7 - speed1
int btn2   = 6; //for pin 6 - speed2
int btn3   = 5; //for pin 5 - speed3
int btn4   = 4; //for pin 4 - speed4

int speed1  = 100; // speed 100%
int speed2   = 75; // speed 75%
int speed3   = 50; // speed 50%
int speed4   = 25; // speed 25%

//750-900
int highLevel   = 800;//number to compare with the analog reader
int mediumLevel = 750;//number to compare with the analog reader
int lowLevel    = 700;//number to compare with the analog reader

int output_signal   = 0; //for output value, this goes between 0 and 255 to the pwd

void setup() {
  pinMode(2,INPUT);//this button stop the process
  
  pinMode(btn1,INPUT);//  100% power for 8s and 75% power for 60s
  pinMode(btn2,INPUT);//   85% power for 100s
  pinMode(btn3,INPUT);//   75% power for 100s
  pinMode(btn4,INPUT);//   50% power for 100s

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
  
  if(digitalRead(btn1)){
    Serial.print("100 Signal");
    Serial.println(output_signal);
    option=1;
    Power(speed1);
    }
  if(digitalRead(btn2)){
    Serial.print("75 Signal");
    Serial.println(output_signal);
    option=2;
    Power(speed2);
    }
  if(digitalRead(btn3)){  
    Serial.print("50 Signal");
    Serial.println(output_signal);
    option=3;
    Power(speed3);
    }
  if(digitalRead(btn4)){  
    Serial.print("25 Signal");
    Serial.println(output_signal);
    option=4;
    Power(speed4);
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

void Power(int value){
  output_signal=map(value,0,100,40,130);
  esc_signal.write(output_signal);
}
  
void CheckOption(){
  switch (option) {
  case 1:
    Serial.println("100%");
    if(count>=100){
      BotonStop();
      }
    break;
  case 2:
    Serial.println("75%");
    if(count>=600){
      BotonStop();
      }
      break;
  case 3:
    Serial.println("50%");
    if(count>=1200){
      BotonStop();
      }
    break;
  case 4:
    Serial.println("25%");
    if(count>=1200){
      BotonStop();
      }
    break;
  default:
    // Serial.println("0%");
    BotonStop();
    break;
}
  }
