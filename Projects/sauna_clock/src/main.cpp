#include <Arduino.h>
#include <Servo.h>
//#include <IRremote.h>



int IRsig = 4;
int Servosig = 15;
int servoval = 0;

// put function declarations here:

Servo myservo;  // create Servo object to control a servo

void setup() {
  // put your setup code here, to run once:s
  Serial.begin(9600);
  Serial.println("HELLO");
  pinMode(IRsig, INPUT);
  pinMode(Servosig, OUTPUT);
  digitalWrite(Servosig, LOW);
  myservo.attach(9);  // attaches the servo on pin 9 to the Servo object
  myservo.write(0);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int IRval = digitalRead(IRsig);

  if (IRval == LOW) {
    digitalWrite(Servosig, HIGH);
    Serial.println(IRval);
    Serial.println("Something Detected");
    servoval = 0;
    myservo.write(180);
    delay(1000);

  } else {
    digitalWrite(Servosig, LOW);
    Serial.println(IRval);
  }

}


