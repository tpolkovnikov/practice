char income_symbol;

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
  value+=15;
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
  value -= 15;
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

void rightfront(){
  pinMode(5,INPUT);
  pinMode(11,INPUT);
  pinMode(6,OUTPUT);
  pinMode(3,OUTPUT);
  analogWrite(6,-150);
  analogWrite(3,-50);
}

void leftfront(){
  pinMode(5,INPUT);
  pinMode(11,INPUT);
  pinMode(6,OUTPUT);
  pinMode(3,OUTPUT);
  analogWrite(3,-150);
  analogWrite(6,-50);
}

void razvorotR(){
  pinMode(3,INPUT);
  pinMode(6,INPUT);
  pinMode(5,OUTPUT);
  pinMode(11,OUTPUT);
  analogWrite(5,-50);
  analogWrite(11,50);
}
  
void razvorotL(){
  pinMode(3,INPUT);
  pinMode(6,INPUT);
  pinMode(5,OUTPUT);
  pinMode(11,OUTPUT);
  analogWrite(11,-50);
  analogWrite(5,50);
 } 
 
void setup() {
  Serial.begin(19200);
}

void loop(){
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
