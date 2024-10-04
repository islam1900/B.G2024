//UltraSonic
#define CF_Trig 2
#define CF_Echo A0 
#define LF_Trig 4 
#define LF_Echo A1
#define RF_Trig 6 
#define RF_Echo 7 
#define CB_Trig 8
#define CB_Echo 9
#define RB_Trig 10
#define RB_Echo 11
#define LB_Trig 12
#define LB_Echo 13

float LF_Distance, RF_Distance, CF_Distance, LB_Distance, RB_Distance, CB_Distance;
int laffa=0;
int sp= 60;
long before,after,afffter;

//motors
#include <Servo.h>
Servo servo;
#define servo_r1 10   //120- 
#define servo_l2 11   //120+
#define en 5
#define in3 A3
#define in4 A2
#define button A4
#define raspil A6
#define raspir A7


char rot='n';

void Move(int v ,int dir ,long sec){
  
  if (v>0)
    {
    int sp= map (v,1,100,0,255);  
    analogWrite(en,sp);
    digitalWrite(in3,1);
    digitalWrite(in4,0);
    }

  else if (v<0)
    {
    int sp= map (v,-1,-100,0,255);
    analogWrite(en,sp);
    digitalWrite(in3,0);
    digitalWrite(in4,1);
    }
  else if(v==0)
    {
    digitalWrite(in3,1);
    digitalWrite(in4,1);
    analogWrite(en,0);
    }
int steer;
int servoCenter=97;
  if(dir>=0)
  {
  steer=map(dir,0,100,servoCenter,50);
  }
  else if(dir<0) 
  {
  steer=map(dir,-1,-100,servoCenter,136);
  } 
  servo.write(steer);
  delay (sec);
}

void ultra(int F , int B){
  float Time;
 if (F==1)
   {
    digitalWrite(RF_Trig,1);
    delayMicroseconds(10);
    digitalWrite(RF_Trig,0);
    Time = pulseIn(RF_Echo, 1, 9000);
    RF_Distance = Time * 0.034 / 2;
    digitalWrite(LF_Trig,1);
    delayMicroseconds(10);
    digitalWrite(LF_Trig,0);
    Time = pulseIn(LF_Echo, 1, 9000);
    LF_Distance = Time * 0.034 / 2;
    digitalWrite(CF_Trig,1);
    delayMicroseconds(10);
    digitalWrite(CF_Trig,0);
    Time = pulseIn(CF_Echo, 1, 9000);
    CF_Distance = Time * 0.034 / 2;
    }
 if (B==1)
    {     
    digitalWrite(RB_Trig,1);
    delayMicroseconds(10);
    digitalWrite(RB_Trig,0);
    Time = pulseIn(RB_Echo, 1, 9000);
    RB_Distance = Time * 0.034 / 2;
    digitalWrite(LB_Trig,1);
    delayMicroseconds(10);
    digitalWrite(LB_Trig,0);
    Time = pulseIn(LB_Echo, 1, 9000);
    LB_Distance = Time * 0.034 / 2;
    digitalWrite(CB_Trig,1);
    delayMicroseconds(10);
    digitalWrite(CB_Trig,0);
    Time = pulseIn(CB_Echo, 1, 9000);
    CB_Distance = Time * 0.034 / 2;
    }
       
  if(LF_Distance==0){LF_Distance=100.0;}
  if(LB_Distance==0){LB_Distance=100.0;}
  if(RF_Distance==0){RF_Distance=100.0;}
  if(CF_Distance==0){CF_Distance=100.0;}
  if(RB_Distance==0){RB_Distance=100.0;}
  if(CB_Distance==0){CB_Distance=100.0;}
}


void center(long sec){
  long t_time = millis();
  while((millis()-t_time)<sec)
  {
    ultra(1,0);
  if(RF_Distance <15)
  {
    Move(sp,-20,10);
  }
  else if(RF_Distance <30)
  {
    Move(sp,-15,10);
  }
  else if(LF_Distance <15)
  {
    Move(sp,20,10);
  }
  else if(LF_Distance <30)
  {
    Move(sp,15,10);
  }
  else
  {
    Move(sp,0,10);
  }
}
}
void test(char what){
 if (what=='u')
      {
 ultra(1,1);
 Serial.print(CF_Distance);
 Serial.print("  ");
 Serial.print(RF_Distance);
 Serial.print("  ");
 Serial.print(RB_Distance);
 Serial.print("  ");
 Serial.print(CB_Distance);
 Serial.print("  ");
 Serial.print(LB_Distance);
 Serial.print("  ");
 Serial.println(LF_Distance);
      }
 else { 
  Serial.print(analogRead(raspil));
  Serial.print("        ");
  Serial.println(analogRead(raspir));
     }
}

void setup() {

//ultrasonics
pinMode(LF_Trig, OUTPUT);
pinMode(RF_Trig, OUTPUT);
pinMode(CF_Trig, OUTPUT);
pinMode(LF_Echo, INPUT);
pinMode(RF_Echo, INPUT);
pinMode(CF_Echo, INPUT);
pinMode(LB_Trig, OUTPUT);
pinMode(RB_Trig, OUTPUT);
pinMode(CB_Trig, OUTPUT);
pinMode(LB_Echo, INPUT);
pinMode(RB_Echo, INPUT);
pinMode(CB_Echo, INPUT);

//motors
pinMode(in3,OUTPUT);
pinMode(in4,OUTPUT);
pinMode(en,OUTPUT);

pinMode(button, INPUT_PULLUP);


servo.attach(3);

Serial.begin(9600);
  while(digitalRead(button)==1){Move(0,0,1);}Move(0,0,500);

}
