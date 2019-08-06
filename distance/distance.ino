void setup() {
  Serial.begin(9600);
  pinMode(D0, OUTPUT);
  pinMode(D1, OUTPUT);
  pinMode(D2, INPUT);
}

void loop() {
  digitalWrite(D1, HIGH);
  delayMicroseconds(10);
  digitalWrite(D1, LOW);

  int distance = pulseIn(D2, HIGH) * 17 / 1000; //거리계산
  Serial.print(distance);
  Serial.println("cm");

  int Time = map(distance, 0, 400, 0, 4000);  //distance를 매핑하는것
  //0 ~ 400 을 0 ~ 4000으로 바꾼 것이다.

  if(distance > 400){
    digitalWrite(D0, LOW);
  }else{
    digitalWrite(D0, HIGH);
    delay(Time);
    digitalWrite(D0, LOW);
    delay(Time);
  }
}
