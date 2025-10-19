#include <Arduino.h>
#include <Servo.h>

int AnswerList[3] = {23,72,91}; // 期待する温度リスト
int WhereNow = 0; // 期待する入力
int margin = 10; // マージン指定 小さいほどプレイヤーに厳しい

Servo myservo;  // サーボオブジェクトの作成



void openbox() {
  // 開錠処理
  Serial.println("Box Opened!");
  myservo.attach(9); // サーボを9番ピンに接続
  myservo.write(90); // サーボを90度に回転
}

void clear() {
  // クリア処理
  Serial.println("Game Clear!");
  openbox();
  while (1) {
    // 無限ループで止める
  }
}

void setup() {
  // put your setup code here, to run once:s
  Serial.begin(9600);
  Serial.println("Game Start!");
  myservo.write(0); // サーボを初期位置に戻す
}

void loop() {
  // put your main code here, to run repeatedly:s
  float temp = ((analogRead(4) / 1023.0) * 120); // ぽテンションメーターの値を温度に変換
  Serial.println(temp);
  if (abs(temp - AnswerList[WhereNow]) < margin) { // 期待する温度に近いか
    Serial.println("Next temp");
    WhereNow ++;
  }
  if (WhereNow >= 3) { // 3つの温度をクリアしたか
    clear();
  }
  delay(500);
}

