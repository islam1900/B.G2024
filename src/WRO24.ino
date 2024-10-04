#include "WRO24.h"

void loop() 
{
 ultra(1,0);
  
if (analogRead(raspil)>700)
{
  before = millis();
  while (analogRead(raspil)>700){
    Move(35,-50,1);
  }
  after = millis();
  Move(35,0,700);
  Move(35,40,(after - (before+70)));

}
else if (analogRead(raspir)>700)
{
   before = millis();
  while (analogRead(raspir)>700){
    Move(35,40,1);
  }
  after = millis();
  Move(35,0,700);
  Move(35,-40,(after - (before+70)));
  Move(35,0,500);
}
else if(CF_Distance <25)
{
  Move(0,0,200);
  ultra(1,0);
  if(RF_Distance > LF_Distance)
  {
    Move(-60,-70,1700);
  }
  else
  {
    Move(-60,70,1600);
  }
}

else
{
  sp=40;
  ultra(1,0);
  if(RF_Distance <20)
  {
    Move(sp,-30,10);
  }
  else if(LF_Distance <20)
  {
    Move(sp,30,10);
  }
  else
  {
  Move(sp,0,10);
  }
}
}


void start(){
  for(int i=0;i<12;i++)
  {
  ultra(1,1);
  while((LF_Distance<90||LB_Distance<90) && (RF_Distance<90 || RB_Distance<90))
  {
    ultra(1,1);
    center(10);
  }
  
    Move(-40,0,5);
   if(rot =='n'){
    if(RF_Distance >90 )
    {
      rot= 'r';
    }
   else
    {
      rot='l';
    }
   }
   ultra(1,0);
   if (CF_Distance < 50)
   {
    Move(-60,0,150);
    Move(0,0,250);
    Move(-sp,0,930);
    Move(60,0,50);
    laffa=1;
   }
  if (rot == 'r')
  {
    ultra(1,1);
    if(LF_Distance<LB_Distance)
    {
      while(LF_Distance!=LB_Distance)
      {
        Move(50,20,10);
        ultra(1,1);
      }
    }
    else if(LB_Distance<LF_Distance)
    {
      while(LF_Distance!=LB_Distance)
      {
        Move(50,-20,10);
        ultra(1,1);
      }
    }
      if (laffa==0)
      {
      Move(sp,70,300);
      ultra(1,0);
      while(CF_Distance < 90){
      ultra(1,0);
      Move(sp,70,10);
      }
     Move(sp,70,60);
    }
    else
    {
     Move(0,70,150);
     Move(sp,70,560);
     laffa=0;
    }

  }
  else
  {
    if (laffa==0)
    {
    Move(sp,-70,300);
    ultra(1,0);
    while(CF_Distance < 90){
    ultra(1,0);
    Move(sp,-70,10);
    }
     Move(60,-70,60);
    }
    else
    {
     Move(0,-70,150);
     Move(sp,-70,800);
     laffa=0;
    }

  }
    center(1150);    
  }
  Move (-50,0,50);
  Move(0,0,100000000);


}
