#include <SPI.h>
#include <MFRC522.h>
#include <lorawan.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>


#define ssKanan 32
#define rstKanan 17
#define ssKiri 33
#define rstKiri 16
MFRC522 rfKiri(ssKiri, rstKiri);
MFRC522 rfKanan(ssKanan, rstKanan);
Servo servoKiri;
Servo servoKanan;
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, -1);


const char *devAddr = "6523dfef";
const char *appSKey = "6523dfef9a909e84178a7aa504663f65";
const char *nwkSKey = "6523dfef717760c2600978e8c8e10830";
const sRFM_pins RFM_pins = {
  //board ungu
  .CS = 25,
  .RST = 13,
  .DIO0 = 27,
  .DIO1 = 26,
};

struct cardData {
  String id;
  bool status;
};

cardData cards[] = {
  {"16511018173", 0}, //card1
  {"2023817644", 0}, //card2
  {"6801522644", 0}, //card3
  {"18024522744", 0}, //card4
  {"0424922944", 0}, //card5
  {"18012223744", 0}, //card6
  {"5211422844", 0}, //card7
  {"048323444", 0}, //card8
  {"1969323344", 0}, //card9
  {"2125120744", 0}, //card10
  {"2129023344", 0} //card11
};

int cardTotal = sizeof(cards) / sizeof(cards[0]);
int counter;
int tersedia;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(25, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  digitalWrite(16, LOW);
  digitalWrite(17, LOW);
  Serial.begin(115200);
  servoSetup();
  spiffSetup();
  readData();
  oledSetup();
  cardCount();
  Serial.println("RFID ready to tap on...");
}
void loop() {
  cardDetect();
}
