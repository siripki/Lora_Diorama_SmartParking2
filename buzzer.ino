void buzzerBep(){
  digitalWrite(4, HIGH);
  delay(80);
  digitalWrite(4, LOW);
}

void buzzerBepBep(){
  digitalWrite(4, HIGH);
  delay(60);
  digitalWrite(4, LOW);
  delay(60);
  digitalWrite(4, HIGH);
  delay(60);
  digitalWrite(4, LOW);
}

void buzzerBepLong(){
  digitalWrite(4, HIGH);
  delay(300);
  digitalWrite(4, LOW);
  delay(300);
  digitalWrite(4, HIGH);
  delay(300);
  digitalWrite(4, LOW);
  delay(300);
}