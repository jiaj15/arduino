#include <PID_v1.h>
/*
RED MOTOR+ TO RED POWER+

BLACK MOTOR-  TO BLACK -ground
GREEN ENCODER- TO BROWN -ground
!ALL THE GROUND MUST BE CONNECTED TO THE GROUND OF ARDUINO
BLUE ENCODER + TO ORANGE- arduino 4
YELLOW A TO GREY arduino -2
WHITE B TO WHITE arduino -3
*/
int CounterA=0,  CounterB=0;
unsigned long time = 0, old_time = 0; // Ã¦â€”Â¶Ã©â€”Â´Ã¦Â â€¡Ã¨Â®Â°
int tm=100;//50ms
float v;//Ã©â‚¬Å¸Ã¥ÂºÂ¦
int setspeed=500;
int encodera=         0;
int encoderb=         1;
int voltageEncoderP=  4;
//int voltageEncoderG=  5;
int IN1=              7;
int IN2=              8;
int pwm=              9;
//void motorRun(int setspeed);
//PID
//Define Variables we'll be connecting to
double Setpoint, Input, Output;

//Specify the links and initial tuning parameters
PID myPID(&Input, &Output, &Setpoint,2,0,0, DIRECT);


void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
attachInterrupt(encodera,Count_CallBacka, FALLING);
attachInterrupt(encoderb,Count_CallBackb, FALLING);
pinMode(voltageEncoderP,OUTPUT);
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(pwm,OUTPUT);

//initialize the variables we're linked to
  Input = v;
  Setpoint = setspeed;
  //turn the PID on
  myPID.SetMode(AUTOMATIC);
  myPID.SetOutputLimits(100, 1023);  // Ã¨Â¾â€œÃ¥â€¡ÂºÃ¥Å“Â¨100-1023Ã¤Â¹â€¹Ã©â€”Â´

}

void loop() {
//  digitalWrite(IN1, HIGH);
//  digitalWrite(IN2, LOW);
//  analogWrite(pwm,255);
 digitalWrite(voltageEncoderP, HIGH);
  //motorRun(setspeed);
  SpeedDetection();
  

}
bool SpeedDetection()
{
  time = millis();//Ã¤Â»Â¥Ã¦Â¯Â«Ã§Â§â€™Ã¤Â¸ÂºÃ¥ï¿½â€¢Ã¤Â½ï¿½Ã¯Â¼Å’Ã¨Â®Â¡Ã§Â®â€”Ã¥Â½â€œÃ¥â€°ï¿½Ã¦â€”Â¶Ã©â€”Â´ 
  if(abs(time - old_time) >= tm) // Ã¥Â¦â€šÃ¦Å¾Å“Ã¨Â®Â¡Ã¦â€”Â¶Ã¦â€”Â¶Ã©â€”Â´Ã¥Â·Â²Ã¨Â¾Â¾1Ã§Â§â€™
  {  
    detachInterrupt(encodera); // Ã¥â€¦Â³Ã©â€”Â­Ã¥Â¤â€“Ã©Æ’Â¨Ã¤Â¸Â­Ã¦â€“Â­2
    detachInterrupt(encoderb); // Ã¥â€¦Â³Ã©â€”Â­Ã¥Â¤â€“Ã©Æ’Â¨Ã¤Â¸Â­Ã¦â€“Â­3
    
  int  va =(float)CounterA*60*1000/(14*tm);
  int  vb =(float)CounterB*60*1000/(14*tm);
    v=(va+vb)/2;
   // Serial.print("speed:");
    Serial.println(v);
    //Serial.println(" rpm");
    
    //Ã¦ï¿½Â¢Ã¥Â¤ï¿½Ã¥Ë†Â°Ã§Â¼â€“Ã§Â ï¿½Ã¥â„¢Â¨Ã¦Âµâ€¹Ã©â‚¬Å¸Ã§Å¡â€žÃ¥Ë†ï¿½Ã¥Â§â€¹Ã§Å Â¶Ã¦â‚¬ï¿½
    CounterA = 0;   //Ã¦Å Å Ã¨â€žâ€°Ã¥â€ Â²Ã¨Â®Â¡Ã¦â€¢Â°Ã¥â‚¬Â¼Ã¦Â¸â€¦Ã©â€ºÂ¶Ã¯Â¼Å’Ã¤Â»Â¥Ã¤Â¾Â¿Ã¨Â®Â¡Ã§Â®â€”Ã¤Â¸â€¹Ã¤Â¸â‚¬Ã§Â§â€™Ã§Å¡â€žÃ¨â€žâ€°Ã¥â€ Â²Ã¨Â®Â¡Ã¦â€¢Â°
    CounterB = 0;
    old_time=  millis();     // Ã¨Â®Â°Ã¥Â½â€¢Ã¦Â¯ï¿½Ã§Â§â€™Ã¦Âµâ€¹Ã©â‚¬Å¸Ã¦â€”Â¶Ã§Å¡â€žÃ¦â€”Â¶Ã©â€”Â´Ã¨Å â€šÃ§â€šÂ¹   
    attachInterrupt(encodera,Count_CallBacka, FALLING);
    attachInterrupt(encoderb,Count_CallBackb, FALLING);
    return 1;
  }
  else
    return 0;
}
void Count_CallBacka()
{
  CounterA++;
}
void Count_CallBackb()
{
  CounterB++;
}
void motorRun(int setspeed)
{
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  Input = v;
  myPID.Compute();
  analogWrite(pwm,Output);
//Serial.println(Output);
  //analogWrite(pwm,setspeed);
  }




