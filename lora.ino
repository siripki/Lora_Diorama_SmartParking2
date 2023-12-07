void loraSetup() {
  loraOn();
  if (!lora.init()) {
    Serial.println("Problem : Lora");
    delay(2000);
    return;
  }
  lora.setDeviceClass(CLASS_A);  // Set LoRaWAN Class change CLASS_A
  lora.setDataRate(SF10BW125);
  lora.setFramePortTx(5);
  lora.setChannel(MULTI);

  lora.setTxPower(20);
  lora.setNwkSKey(nwkSKey);
  lora.setAppSKey(appSKey);
  lora.setDevAddr(devAddr);
}

void sendData_Lora(String msg) {
  loraSetup();
  char myStr[msg.length() + 1];
  msg.toCharArray(myStr, msg.length() + 1);
  Serial.println(myStr);  //debug
  Serial.println(" ");
  lora.sendUplink(myStr, strlen(myStr), 0);
  lora.update();
  //delay(2000);
}

void loraOff(){
  digitalWrite(13, LOW); //rst low to disable
  digitalWrite(25, HIGH);
}
void loraOn(){
  digitalWrite(13, HIGH); //rst high then low for min 5ms then high
  digitalWrite(25, HIGH); //cs high to enable
}