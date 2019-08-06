void setup() {
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  char command;

  if(Serial.available() > 0){ //Serial을 PC라고 생각하면 된다.
    //즉, PC쪽에서 데이터가 왔니 라고 물어보는 것 이다.
    //또한 1바이트씩 읽으면서 데이터가 있는지 확인한다.
    command = Serial.read();

    switch(command){
      case 'g':
        digitalWrite(D0, HIGH);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        delay(500);
        break;
      case 'b':
        digitalWrite(D0, LOW);
        digitalWrite(D1, HIGH);
        digitalWrite(D2, LOW);
        delay(500);
        break;
      case 'r':
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, HIGH);
        delay(500);
        break;
      case 'd':
        digitalWrite(D0, LOW);
        digitalWrite(D1, LOW);
        digitalWrite(D2, LOW);
        delay(500);
        break;
    }
/*
    if(command == 'g'){
      digitalWrite(D0, HIGH);
      digitalWrite(D1, LOW);
      digitalWrite(D2, LOW);
      delay(500);
    }
    if(command == 'b'){
      digitalWrite(D0, LOW);
      digitalWrite(D1, HIGH);
      digitalWrite(D2, LOW);
      delay(500);
    }
    if(command == 'r'){
      digitalWrite(D0, LOW);
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH);
      delay(500);
    }
    
    else{
      digitalWrite(D1, LOW);
      Serial.print("else : ");
      Serial.println(command);
    }
    */
  }
}
