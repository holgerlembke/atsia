/*
     atsiaController: All the same i2c addr

  Command interface
        76543210
        00SLRIAA

    AA ID
    L  1: is LED command
    S  x: state of LED
*/

#include <Wire.h>

const byte i2caddr = 0x42;


//******************************************************
void i2cscanner() {
  for (int i = 0x0b; i < 0x78; i++) {
    Wire.beginTransmission(i);
    int r = Wire.endTransmission();

    if (r == 0) {
      Serial.print(F("0x"));
      Serial.println(i, HEX);
    }

  }
  Serial.println(".");
  delay(1000);

}


void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.print(F("atsiaController "));
  Serial.print(F(__DATE__));
  Serial.print(" ");
  Serial.print(F(__TIME__));
  Serial.println();

  Wire.begin();
  i2cscanner();
}

void loop() {
  static byte id = 0;
  static bool state[4] = {false, false, false, false};

  Wire.beginTransmission(i2caddr);
  byte cmd = id | 0b10000 | (0b100000 * state[id]);
  Wire.write(&cmd, sizeof(cmd));
  int r = Wire.endTransmission();

  state[id] = ! state[id];
  id = (id == 3) ? 0 : id + 1;

  delay(1000); 
}

//
