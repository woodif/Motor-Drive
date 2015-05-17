#include <TimerOne.h>
#define sentsivity 0.004338461f
#define zerodiff 6.0f
int right = 8;
int pwmR =9;  
int pwmL = 10;
int left = 11;

int analogPin = A0;     // potentiometer wiper (middle terminal) connected to analog pin 3

float current = 0;
float ref = 2.00;
float pwm = 0;
float error = 0;
float time = 0 ;

void setup() 
{
  
  pinMode(8, OUTPUT); //right
  pinMode(11, OUTPUT); //left
  
 Serial.begin(9600);
 
 analogReference(INTERNAL);
//---------------------------------------------- Set PWM frequency for D3 & D11 ------------------------------
  
TCCR1B = TCCR1B & B11111000 | B00000001;    // set timer 1 divisor to     1 for PWM frequency of 31372.55 Hz
//TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
//TCCR1B = TCCR1B & B11111000 | B00000011;    // set timer 1 divisor to    64 for PWM frequency of   490.20 Hz (The DEFAULT)
//TCCR1B = TCCR1B & B11111000 | B00000100;    // set timer 1 divisor to   256 for PWM frequency of   122.55 Hz
//TCCR1B = TCCR1B & B11111000 | B00000101;    // set timer 1 divisor to  1024 for PWM frequency of    30.64 Hz
  
  Timer1.initialize(500); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
  Timer1.attachInterrupt( timerIsr ); // attach the service routine here
}
 
void loop()
{
  // Main code loop
  // TODO: Put your regular (non-ISR) logic here
digitalWrite(8,HIGH); //right
digitalWrite(11,LOW); //left

}
 
/// --------------------------
/// Function Right///
/// --------------------------
void timerIsr()
{
    digitalWrite(8,HIGH);
    digitalWrite(11,LOW);
    analogWrite(10, 0);
    
    float tmp = micros();
    static int count;
    digitalWrite(13,1);
    float value = analogRead(analogPin) ;    // read the input pin
    current = (value-zerodiff)*sentsivity ;
    error = ref - current;
    pwm += error;
    if (pwm<0)pwm = 0;
    if (pwm>255)pwm = 255;
    analogWrite(9, pwm);  // analogRead values go from 0 to    //1023, analogWrite values from 0 to 255
    digitalWrite(13,0);
    
    
    if (count >= 50)
    {
      count = 0;
      Serial.println(current);             // time
    }
    count ++;
    time = micros()- tmp;
}
