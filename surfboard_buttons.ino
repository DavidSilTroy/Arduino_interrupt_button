#include<TimerOne.h> //Libreria de interrupción de tiempo

int option  = 0;  //this is to know witch button was touched
int count   = 0;  //this is to know how much time the output will be working

int btn100  = 8;  //for pin 8
int btn75   = 7;  //for pin 7
int btn50   = 12; //for pin 12
int btn25   = 13; //for pin 13

int output_signal   = 0; //for output value, this goes between 0 and 255 to the pwd

void setup() {
  pinMode(2,INPUT);//this button stop the process
  
  pinMode(btn100,INPUT);//  100% power for 8s and 75% power for 60s
  pinMode(btn75,INPUT);//   75% power for 100s
  pinMode(btn50,INPUT);//   50% power for 100s
  pinMode(btn25,INPUT);//   25% power for 100s

  pinMode(6,OUTPUT); // output signal
  
  attachInterrupt(digitalPinToInterrupt(2),BotonStop,RISING); //this button will work even if something else is in process

  Serial.begin(9600); //to print the values
  
}

void loop() {
  
  if(digitalRead(btn100)){
    output_signal=map(100,0,100,0,255);
    option=1;
    Power100();
    }
  if(digitalRead(btn75)){
    output_signal=map(75,0,100,0,255);
    option=2;
    Power75();
    }
  if(digitalRead(btn50)){
    output_signal=map(50,0,100,0,255);
    option=3;
    Power50();
    }
  if(digitalRead(btn25)){
    output_signal=map(25,0,100,0,255);
    option=4;
    Power25();
    }
    
  CheckOption();
  count+=1;
  delay(100);
}

void BotonStop(){
//pin2 button
  option=0;
  count=0;
  analogWrite(6, 0);
}

void Power100(){
  analogWrite(6,output_signal);
  }
void Power75(){
  analogWrite(6,output_signal);
  }
void Power50(){
  analogWrite(6,output_signal);
  }
void Power25(){
  analogWrite(6,output_signal);
  }
  
void CheckOption(){
  switch (option) {
  case 1:
    if(count==80){
      output_signal=map(75,0,100,0,255);
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
