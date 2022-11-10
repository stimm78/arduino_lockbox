#include <SoftwareSerial.h>

int bluetoothTx = 2; //bluetooth transmit serial data pin
int bluetoothRx = 3; //bluetooth receive serial data pin
SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

int m1Pin1 = 5; //front motor pins
int m1Pin2 = 6;
int m2Pin1 = 11; //back motor pins
int m2Pin2 = 12;

char bt_command = 0;
void setup() {
  Serial.begin(9600);
  bluetooth.begin(9600);
  pinMode(m1Pin1,OUTPUT);
  pinMode(m1Pin2,OUTPUT);
  pinMode(m2Pin1,OUTPUT);
  pinMode(m2Pin2,OUTPUT);
}

void loop() {
  if (bluetooth.available() > 0) {
    bt_command = bluetooth.read();
    Serial.println(bt_command); //print for debugging
    switch(bt_command) {
      case 'F': //forward
        digitalWrite(m1Pin1, HIGH);
        digitalWrite(m1Pin2, LOW);
        digitalWrite(m2Pin1, HIGH);
        digitalWrite(m2Pin2, LOW);
        break;
      case 'B': //backward
        digitalWrite(m1Pin1, LOW);
        digitalWrite(m1Pin2, HIGH);
        digitalWrite(m2Pin1, LOW);
        digitalWrite(m2Pin2, HIGH);
        break;
      case 'L': //left
        digitalWrite(m1Pin1, LOW);
        digitalWrite(m1Pin2, LOW);
        digitalWrite(m2Pin1, HIGH);
        digitalWrite(m2Pin2, LOW);
        break;
      case 'R': //right
        digitalWrite(m1Pin1, HIGH);
        digitalWrite(m1Pin2, LOW);
        digitalWrite(m2Pin1, LOW);
        digitalWrite(m2Pin2, LOW);
        break;
      case 'S': //stop
        digitalWrite(m1Pin1, LOW);
        digitalWrite(m1Pin2, LOW);
        digitalWrite(m2Pin1, LOW);
        digitalWrite(m2Pin2, LOW);
        break;
    }
  }
}
