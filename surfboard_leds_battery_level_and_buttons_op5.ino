#include <Servo.h>
Servo esc_signal;

int option  = 0;  //this is to know witch button was touched
int count   = 0;  //this is to know how much time the output will be working
int count_battery   = 0;  //this is to read the battery after an specific time

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


int highLevel   = 400;//number to compare with the analog reader
int lowLevel    = 200;//number to compare with the analog reader

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
  
  //setting a new variable battery level decided by the first read
  if (analogRead(1)>500)
  {
    highLevel = analogRead(1) - 150;
    lowLevel    = analogRead(1)/3;
  }
  

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

  //Comentar esto luego de usar
  Serial.print("Baterry read:");
  Serial.println(analogRead(1));

  if (count_battery>=60){
    CheckBattery(analogRead(1));
    count_battery=0;
  }

  count+=1;
  count_battery+=1;
  delay(100);
  
}

void BotonStop(){
//pin2 button
  option=0;
  count=0;
  esc_signal.write(30);
}

void highbattery(){
  digitalWrite(greenLed,HIGH);
  digitalWrite(redLed,HIGH);
  digitalWrite(yellowLed,HIGH);
}
void midbattery(){
  digitalWrite(yellowLed,HIGH);
  digitalWrite(redLed,HIGH);
  digitalWrite(greenLed,LOW);
}
void lowbattery(){
  digitalWrite(redLed,HIGH);
  digitalWrite(yellowLed,LOW);
  digitalWrite(greenLed,LOW);
}
void battery_leds_off(){
  digitalWrite(yellowLed,LOW);
  digitalWrite(redLed,LOW);
  digitalWrite(greenLed,LOW);
}


void CheckBattery(int level){
   //Serial.println(level);
    if(level<=lowLevel){
      lowbattery();
    }else{
      if(level>=highLevel){
        highbattery();
      } else{
        if(level<highLevel && level>lowLevel){
          midbattery();
        }else{
          //this shouldn't happend actually....
          Serial.print("Recalculation needed for the battery reader");
          battery_leds_off();
        }
      }
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
