char income_symbol;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(19200);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0){
    income_symbol = Serial.read();
      
     if (income_symbol == 'F'){ 
      //forward();
      Serial.print("F");
      Serial.println(income_symbol, 1); // печатает в консоль символ
      pinMode(5,OUTPUT);
      pinMode(11,OUTPUT);
      pinMode(3,INPUT);
      pinMode(6,INPUT);
      digitalWrite(5,LOW);
      digitalWrite(11,LOW);
     }
     if (income_symbol == 'B'){ 
      //forward();
      Serial.print("B");
      Serial.println(income_symbol, 1); // печатает в консоль символ
      pinMode(3,OUTPUT);
      pinMode(6,OUTPUT);
      pinMode(5,INPUT);
      pinMode(11,INPUT);
      digitalWrite(3,LOW);
      digitalWrite(6,LOW);
    }
     if (income_symbol == 'S'){ 
      //forward();
      Serial.print("S");
      Serial.println(income_symbol, 1); // печатает в консоль символ
      pinMode(3,INPUT);
      pinMode(6,INPUT);
      pinMode(5,INPUT);
      pinMode(11,INPUT);
    }
  }
}
