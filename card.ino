void cardDetect(){
  loraOff();
  SPI.begin();
  rfKiri.PCD_Init();
  rfKanan.PCD_Init();
  if (rfKiri.PICC_IsNewCardPresent()) {
    if (rfKiri.PICC_ReadCardSerial()) {
      String rfUidIn = "";
      Serial.println("RF IN");
      for (int i = 0; i < rfKiri.uid.size; i++) {
        if (rfKiri.uid.uidByte[i] < 0x10) {
          uint8_t rawUid1 = 0;
          rfUidIn += rawUid1;
        }
        uint8_t rawUid2 = rfKiri.uid.uidByte[i];
        rfUidIn += rawUid2;
      }
      cardCheckIn(rfUidIn);
      // Serial.println();
      // Serial.println("String : "+rfUid+"");
      rfKiri.PICC_HaltA();       // halt PICC
      rfKiri.PCD_StopCrypto1();  // stop encryption on PCD
    }
  }
  if (rfKanan.PICC_IsNewCardPresent()) {
    if (rfKanan.PICC_ReadCardSerial()) {
      String rfUidOut = "";
      Serial.println("RF OUT");
      for (int i = 0; i < rfKanan.uid.size; i++) {
        if (rfKanan.uid.uidByte[i] < 0x10) {
          uint8_t rawUid3 = 0;
          rfUidOut += rawUid3;
        }
        uint8_t rawUid4 = rfKanan.uid.uidByte[i];
        rfUidOut += rawUid4;
      }
      cardCheckOut(rfUidOut);
      // Serial.println();
      // Serial.println("String : "+rfUid+"");
      rfKanan.PICC_HaltA();       // halt PICC
      rfKanan.PCD_StopCrypto1();  // stop encryption on PCD
    }
  }
}
void cardCheckIn(String &var) {
  Serial.println(var);
  bool flag = false;
  bool flag2 = false;
  
  for (int i = 0; i < cardTotal; i++) {
    if (var == cards[i].id && cards[i].status == 0 && tersedia>0) {
      cards[i].status = 1;
      Serial.print("ID");
      Serial.print(i + 1);
      Serial.println(" IN");
      oledPrint(String(counter), String(tersedia), String("Akses Masuk"));
      buzzerBep();
      servoKiriOn();
      flag = true;
      break;
    } else if (var == cards[i].id && cards[i].status != 0) {
      Serial.println("Sudah Masuk");
      oledPrint(String(counter), String(tersedia), String("Sudah Tap"));
      buzzerBepBep();
      delay(500);
      oledPrint(String(counter), String(tersedia), String("Ready..."));
      flag2 = true;
      break;
    }
  }
  
  if (!flag && !flag2) {
    Serial.println("Akses Ditolak!");
    oledPrint(String(counter), String(tersedia), String("Akses Ditolak!"));
    buzzerBepLong();
    oledPrint(String(counter), String(tersedia), String("Ready..."));
    delay(500);
  } else if (flag) {
    String data;
    codeJson(data);
    writeFile("/cardStatus.txt", data.c_str());
    cardCount();
  }
}

void cardCheckOut(String &var) {
  Serial.println(var);
  bool flag = false;
  bool flag2 = false;
  
  for (int i = 0; i < cardTotal; i++) {
    if (var == cards[i].id && cards[i].status == 1) {
      cards[i].status = 0;
      Serial.print("ID");
      Serial.print(i + 1);
      Serial.println(" OUT");
      oledPrint(String(counter), String(tersedia), String("Akses Keluar"));
      buzzerBep();
      servoKananOn();
      flag = true;
      break;
    } else if (var == cards[i].id && cards[i].status != 1) {
      Serial.println("Sudah Keluar");
      oledPrint(String(counter), String(tersedia), String("Sudah Tap"));
      buzzerBepBep();
      delay(500);
      oledPrint(String(counter), String(tersedia), String("Ready..."));
      flag2 = true;
      break;
    }
  }
  
  if (!flag && !flag2) {
    Serial.println("Akses Ditolak!");
    oledPrint(String(counter), String(tersedia), String("Akses Ditolak!"));
    buzzerBepLong();
    oledPrint(String(counter), String(tersedia), String("Ready..."));
    delay(500);
  } else if (flag) {
    String data;
    codeJson(data);
    writeFile("/cardStatus.txt", data.c_str());
    cardCount();
  }
}

void cardCount() {
  counter = 0;
  for (int i = 0; i < cardTotal; i++) {
    if (cards[i].status) {
      counter++;
    }
  }
  tersedia = 5 - counter;
  Serial.println("Slot Terpakai : "+ String(counter));
  Serial.println("Slot Tersedia : "+ String(tersedia));
  oledPrint(String(counter), String(tersedia), String("Uploading data..."));
  sendData_Lora("{\"Terisi\":" + String(counter) + ",\"Tersedia\":" + String(tersedia) + "}");
  oledPrint(String(counter), String(tersedia), String("Ready..."));
  
}