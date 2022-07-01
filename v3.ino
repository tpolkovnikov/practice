#include <FastLED.h>
#include <Servo.h>
// Количество светодиодов
#define NUM_LEDS 7
// Номер порта
#define LED_PIN 10
// Массив светодиодов
CRGB leds[NUM_LEDS];

char income_symbol;

// для оптического датчика
const int prx_pin = 4;
byte v;

// для ультразвукового дальномера
const int echoPin = 8;
const int trigPin = 7;
long duration,cm;
Servo Servo1;
int servoPin=9;

void back(){
 pinMode(3,INPUT);
 pinMode(6,INPUT);
 pinMode(5,OUTPUT);
 pinMode(11,OUTPUT);
 Serial.print("F");
 int value=0;
 while(value!=255){
  analogWrite(3,value);
  analogWrite(6,value);
  value+=5;
  }
}

void front(){
 pinMode(6,OUTPUT);
 pinMode(3,OUTPUT);
 pinMode(5,INPUT);
 pinMode(11,INPUT);
 Serial.print("B");
 int value = 0;
 while(value!=-255){
  analogWrite(3,value);
  analogWrite(6,value);
  value -= 5;
  }
}

void stop(){
  Serial.print("S");
  Serial.println(income_symbol, 1); // печатает в консоль символ
  analogWrite(3,0);
  analogWrite(6,0);
  analogWrite(5,0);
  analogWrite(11,0);
}

void rightback(){
  pinMode(6,INPUT);
  pinMode(3,INPUT);
  pinMode(5,OUTPUT);
  pinMode(11,OUTPUT);
  analogWrite(5,150);
  analogWrite(11,50);
}

void leftback(){
  pinMode(3,INPUT);
  pinMode(6,INPUT);
  pinMode(5,OUTPUT);
  pinMode(11,OUTPUT);
  analogWrite(5,50);
  analogWrite(11,150);
}

void leftfront(){
  pinMode(5,INPUT);
  pinMode(11,INPUT);
  pinMode(6,OUTPUT);
  pinMode(3,OUTPUT);
  analogWrite(6,-150);
  analogWrite(3,-50);
}

void rightfront(){
  pinMode(5,INPUT);
  pinMode(11,INPUT);
  pinMode(6,OUTPUT);
  pinMode(3,OUTPUT);
  analogWrite(3,-150);
  analogWrite(6,-50);
}

void razvorotR(){
  pinMode(11,INPUT);
  pinMode(5,INPUT);
  analogWrite(11,0);
  analogWrite(5,150);
}
  
void razvorotL(){
  pinMode(5,INPUT);
  pinMode(11,INPUT);
  analogWrite(5,0);
  analogWrite(11,150);
} 

void back_10(){
  pinMode(3,INPUT);
  pinMode(6,INPUT);
  for (int i = 0;i<10000;i++){
    analogWrite(3,150);
    analogWrite(6,150);
  }
  analogWrite(3,0);
  analogWrite(6,0);
}
 
void setup() {
  Serial.begin(19200);
  // ультразвуковой датчик
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(4, INPUT);
  pinMode(10, OUTPUT);

  // для светодиодиков
  FastLED.addLeds<WS2812,LED_PIN,GRB>(leds,NUM_LEDS).setCorrection(TypicalLEDStrip);
  // яркость светодиодов (макс значение 255) менять можно в любом месте программы
  FastLED.setBrightness(50);
}

void loop(){
  // звуковой датчик
  Servo1.write(90);
  digitalWrite(trigPin,LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration=pulseIn(echoPin,HIGH);
  cm=(duration/2)/29;
  // оптический датчик
  pinMode(prx_pin,INPUT);
  v = digitalRead(prx_pin);
  // условие на наличие тупика
   if((v != 1) || (cm < 23)){
    leds[0] = CHSV(0,0,255);
    leds[2] = CHSV(0,0,255);
    leds[1] = CHSV(0,0,255);
    leds[4] = CHSV(0,0,255);
    leds[6] = CHSV(0,0,255);
    // отправляем информациюю на ленту
    FastLED.show();
    Serial.println(cm);
    stop();
    back_10();
  }
  else{
    leds[0] = CHSV(0,0,0);
    leds[2] = CHSV(0,0,0);
    leds[1] = CHSV(0,0,0);
    leds[4] = CHSV(0,0,0);
    leds[6] = CHSV(0,0,0);
    FastLED.show();
  }
if (Serial.available()>0)
 {
  income_symbol = Serial.read();
  Serial.println(income_symbol);
  switch (income_symbol)
  {
    case 'F': // Движение вперед
      stop();
      front();
      break;
    case 'B': // Движение назад
      stop();
      back();
      break;
    case 'G': // Движение налево вперед
      leftfront();
      break;
    case 'S': // Стоп
      stop();
      break;
    case 'I': // Движение вперед направо
      stop();
      rightfront();
      break;
    case 'H': // Движение назад налево
      stop();
      leftback();
      break;
    case 'J': // Движение назад направо
      stop();
      rightback();
      break;
    case 'R': // Разворот направо 
      stop();
      razvorotR();
      break;
    case 'L': // Разворот налево
      stop();
      razvorotL();
      break;
   }
  }
}
