/*
 * SPDX-FileCopyrightText: 2025 M5Stack Technology CO LTD
 *
 * SPDX-License-Identifier: MIT
 */
/*
 * @Hardwares: M5Core + Unit RFID
 * @Platform Version: Arduino M5Stack Board Manager v2.1.3
 * @Dependent Library:
 * M5Stack@^0.4.6: https://github.com/m5stack/M5Stack
 */
// #include <Arduino.h>
// #include <M5Stack.h>
#include "MFRC522_I2C.h"

MFRC522 mfrc522(0x28); // Create MFRC522 instance.  创建MFRC522实例

void checkRFID(){
  // Serial.println("Please put the card\n\nUID:");
  // Serial.setCursor(40, 47);
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial())
  { // 如果没有读取到新的卡片
    return;
  }
  // Serial.fillRect(42, 47, 320, 20, BLACK);
  for (byte i = 0; i < mfrc522.uid.size; i++)
  { // Output the stored UID data.  将存储的UID数据输出
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println("");
}



void setup(){
  delay(1000);
  Serial.begin(115200);

  Wire.begin();       // Wire init, adding the I2C bus.  Wire初始化, 加入i2c总线
  mfrc522.PCD_Init(); // Init MFRC522.  初始化 MFRC522
  Serial.println("Please put the card\n\nUID:");
}

void loop(){
  checkRFID();
  delay(200);
}


