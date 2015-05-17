#include <TimerOne.h>
#define sentsivity 0.003f
#define zerodiff 5.0f
//setpin number
//int rightout = 8;
//int pwmR =9;  
//int pwmL = 10;
//int leftout = 11;
//
//int sensor = A0;
//
int enablepin = 4;
int controlpin = 5 ;
int pwmin = A1 ;

//Variable
float current = 0;
float ref = 0.50;//
float pwm = 0;
float error = 0;
float time = 0 ;
int timer = 0;
float value = 0;
//
int enable=0;
int control = 0 ;
float fast = 0; 
//int startleft = 0 ;
//int nowdirection=0;
int lastdirection=0;

void setup() 
{

  pinMode(2, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(enablepin, INPUT);
  pinMode(control, INPUT);
  pinMode(13, OUTPUT);

 Serial.begin(115200);
 
analogReference(INTERNAL);

TCCR2B = TCCR2B & B11111000 | B00000001;    // set timer 2 divisor to     1 for PWM frequency of 31372.55 Hz
//TCCR2B = TCCR2B & B11111000 | B00000010;    // set timer 2 divisor to     8 for PWM frequency of  3921.16 Hz
//TCCR2B = TCCR2B & B11111000 | B00000011;    // set timer 2 divisor to    32 for PWM frequency of   980.39 Hz
//TCCR2B = TCCR2B & B11111000 | B00000100;    // set timer 2 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)
//TCCR2B = TCCR2B & B11111000 | B00000101;    // set timer 2 divisor to   128 for PWM frequency of   245.10 Hz
//TCCR2B = TCCR2B & B11111000 | B00000110;    // set timer 2 divisor to   256 for PWM frequency of   122.55 Hz
//TCCR2B = TCCR2B & B11111000 | B00000111;    // set timer 2 divisor to  1024 for PWM frequency of    30.64 Hz
 
 Timer1.initialize(500); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
 Timer1.attachInterrupt( timerIsr ); // attach the service routine here
}
 
void loop()
{
/// --------------------------
/// Function ///

Serial.println(current);
delay(100);
/// --------------------------
}
 

void timerIsr() {
digitalWrite(13,1);
  
  enable = digitalRead(enablepin);
  control = digitalRead(controlpin);
  fast = analogRead(pwmin);

    float tmp = micros();
    static int count;

    
    value = analogRead(A0) ;    // read the input pin
    current = (value-zerodiff)*sentsivity ;
    error = ref - current;
    
    pwm += error;
    
    if (pwm<0)pwm = 0;
    if (pwm>255)pwm = 255;
    ////////////////////////////////////////////////////////////////////////////////
    
    if (control!=lastdirection) timer=20;
    
    ////////////////////////////////////////////////////////////////////////////////
    if(enable == LOW && timer == 0)
    {
        if (control == HIGH)
        {
            digitalWrite(12,LOW);
            analogWrite(11, 0);
            digitalWrite(2,HIGH);
            analogWrite(3, pwm);
        }else{
            digitalWrite(2,LOW);
            analogWrite(3, 0);
            digitalWrite(12,HIGH);
            analogWrite(11, pwm);

        }
    }else{
            digitalWrite(2,LOW);
            digitalWrite(12,LOW);
            analogWrite(3, 0);
            analogWrite(11, 0);
    }
    
    lastdirection=control;
   
    
    
    if (timer>0) timer --;
 
  digitalWrite(13,0);
    
}
