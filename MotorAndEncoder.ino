/*
Name: MotorAndEncoder.ino
Last modified: 2018/09/17 by Jing Jia
Function: read the rotating speed of motor with encoder( if connected, control the speed using pwm)
Tutorials:
1. connect the wires
2. upload the code to arduino
3. open the serial monitor(Tools-> serial monitor)
*/

/*
how to connect wires:

RED( MOTOR+ )   TO          POWER source+
BLACK( MOTOR-)  TO          ground (breadboard)
GREEN( Motor ENCODER- )TO  `ground (breadboard)
BLUE( Motor ENCODER +) TO   arduino 4
YELLOW( Motor ENCODER A)TO  arduino 2
WHITE( Motor ENCODER B) TO  arduino 3

!!!Power Source - and ALL THE GROUND MUST BE CONNECTED TO THE GROUND pin OF ARDUINO


*/
int CounterA=0,  CounterB=0;
unsigned long time = 0, old_time = 0; // 

int tm=100;// calculate the speed every 100ms


/*---------- define pin numbers---------*/
int encodera=         0;
int encoderb=         1;
int voltageEncoderP=  4;
/*----- the is used to control the speed of the motor with L298N using pwm (not necessary if we want to use the encoder only)---*/
int IN1=              7;
int IN2=              8;
int pwm=              9;
//void motorRun(int setspeed);


void setup() {
  // put your setup code here, to run once:
Serial.begin(9600); //open serial
attachInterrupt(encodera,Count_CallBacka, FALLING);//set attach interrupt,read and count signals from encoder A 
attachInterrupt(encoderb,Count_CallBackb, FALLING);//set attach interrupt,read and count signals from encoder B 
pinMode(voltageEncoderP,OUTPUT);// provide power source to encoder
  /* ---set for L298N----*/
pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(pwm,OUTPUT);



}

void loop() {
//  digitalWrite(IN1, HIGH);
//  digitalWrite(IN2, LOW);
//  analogWrite(pwm,255);
 digitalWrite(voltageEncoderP, HIGH);//provide power source to encoder
  //motorRun(setspeed);
 SpeedDetection();// calculate the rotating speed
  

}
bool SpeedDetection()
{
  time = millis();// read the time
  if(abs(time - old_time) >= tm) 
  {  
    detachInterrupt(encodera); // stop counting when calculating the speed
    detachInterrupt(encoderb); // stop counting when calculating the speed
    
  int  va =(float)CounterA*60*1000/(14*tm);
  int  vb =(float)CounterB*60*1000/(14*tm);
    v=(va+vb)/2;
    Serial.print("speed:");
    Serial.println(v);
    Serial.println(" rpm");
    
  
    CounterA = 0;   // clean the counting record
    CounterB = 0;
    old_time=  millis();        
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
 
  
  analogWrite(pwm,Output);
//Serial.println(Output);
  //analogWrite(pwm,setspeed);
  }




