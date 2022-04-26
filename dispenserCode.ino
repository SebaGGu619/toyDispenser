#include <Servo.h>

long mTc(long microseconds) {
   return microseconds / 29 / 2;
}

Servo mare;
Servo mic;

int duratieDreapta() {
   int duration=0;
   digitalWrite(8, LOW);
   delayMicroseconds(2);
   digitalWrite(8, HIGH);
   delayMicroseconds(10);
   digitalWrite(8, LOW);
   duration = pulseIn(7, HIGH);
   return duration;
}

int duratieStanga() {
   int duration=0;
   digitalWrite(13, LOW);
   delayMicroseconds(2);
   digitalWrite(13, HIGH);
   delayMicroseconds(10);
   digitalWrite(13, LOW);
   duration = pulseIn(12, HIGH);
   return duration;
}

void setup() {
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(7,INPUT);
  pinMode(12,INPUT);
  mic.attach(3);
  mare.attach(10);
  mic.write(0);
  mare.write(0);
}

long duratie1,duratie2;
int pozitie1=25,pozitie2=0;
void loop() {
  duratie1=duratieStanga();
  duratie1=mTc(duratie1);
  Serial.println("duratie1:");
  Serial.println(duratie1);
  delay(10);
  duratie2=duratieDreapta();
  duratie2=mTc(duratie2);
  Serial.println("duratie2:");
  Serial.println(duratie2);
  if (duratie1 < 10 and duratie1 > 0) {
    mic.write(pozitie1);
    pozitie1 = pozitie1 + 22;
    if (pozitie1 > 180) {
      delay(1000);
      pozitie1 = 30;
      mic.write(pozitie1);
    }
    while (duratie1 < 10 and duratie1 > 0) {
      duratie1=duratieStanga();
      duratie1=mTc(duratie1);
      delay(100);
    }
  }

  if (duratie2 < 10 and duratie2 > 0) {
    mare.write(pozitie2);
    pozitie2 = pozitie2 + 35;
    if (pozitie2 > 180) {
      delay(1000);
      pozitie2 = 0;
      mare.write(pozitie2);
    }
    while (duratie2 < 10 and duratie2 > 0) {
      duratie2=duratieDreapta();
      duratie2=mTc(duratie2);
      delay(100);
    }
  }
  delay(10);
}
