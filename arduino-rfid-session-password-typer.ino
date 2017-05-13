#include <SPI.h>
#include <MFRC522.h>
#include "Keyboard.h"

#define SS_PIN 5
#define RST_PIN 9

// RFID Reader
MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  Keyboard.begin();
  SPI.begin();
  mfrc522.PCD_Init();
}

void loop() {
  // Looking for new card
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Looking for UID
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  // Serial monitor
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));


  // --------------- BELOW, TYPE YOUR PASSWORD
  
  // Run the loop 4 times
  // and print your password!
  // for (byte i = 0; i < 4; i++) {
  //   Keyboard.print(mfrc522.uid.uidByte[i], HEX);
  // }

  // --------------- END PASSWORD

  Keyboard.releaseAll();

  // Wait 200ms and hit ENTER
  delay(200);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}
