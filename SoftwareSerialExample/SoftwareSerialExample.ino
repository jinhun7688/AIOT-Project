#include <SoftwareSerial.h>

SoftwareSerial mySerial(D5, D6); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  pinMode(D0, OUTPUT);
  Serial.begin(9600); //PC와 NODEMCU와 통신
  mySerial.begin(9600); //NODEMCU간 통신
}

void loop() { // run over and over  
  char AA;
  if (mySerial.available()) { //상대방이 데이터를 보냈는가?
    AA = mySerial.read();
    Serial.print(AA);
    switch(AA){
      case 'a':
        digitalWrite(D0, LOW);
        mySerial.print("LED ON!!\n");
        break;
      case 'b':
        digitalWrite(D0, HIGH);
        mySerial.print("LED OFF!!\n");
        break;
    }
    //Serial.write(mySerial.read());  //데이터를 보냈다면 그것을 읽어와서 나한테 써라
  }
  if (Serial.available()) {
    char BB = Serial.read();
    mySerial.print(BB);
  }
}
