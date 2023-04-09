/*
     atsiaClient: All the same i2c addr

                              +---v---+
                          PB5 |1     8| VCC
           Input+ID0        3 |2     7| 2  SCL
                 ID1        4 |3     6| 1  LED
                          GND |4     5| 0  SDA
                              +-------+
  Command interface
        76543210
        00SLRIAA

    AA ID
    L  1: is LED command
    S  x: state of LED
*/

#include <Wire.h>

const byte i2caddr = 0x42;
const byte PinID0 = 3;
const byte PinID1 = 4;
const byte PinLED = 1;

byte id = 0;

//******************************************************
void wreceive(int c) {
  if (c == 1) {
    byte data = Wire.read();

    if ((data & 0b11) == id) {
      // LED
      if ((data & 0b00010000) != 0) {
        digitalWrite(PinLED, (data & 0b00100000) != 0);
      }
    }
  }
}

//******************************************************
void wrequest() {
  // Wire.write();
}


//******************************************************
void setup() {
  pinMode(PinID0, INPUT_PULLUP);
  pinMode(PinID1, INPUT_PULLUP);
  pinMode(PinLED, OUTPUT);

  Wire.begin(i2caddr);
  Wire.onReceive(wreceive);
  Wire.onRequest(wrequest);

  id = (digitalRead(PinID1) << 1) + digitalRead(PinID0);

  // ein mal Blinken: Wir leben
  digitalWrite(PinLED, HIGH);
  delay(1000);
  digitalWrite(PinLED, LOW);
  delay(2000);

  // ID+1 rausblinken
  for (byte i = 0; i < id + 1; i++) {
    digitalWrite(PinLED, HIGH);
    delay(1000);
    digitalWrite(PinLED, LOW);
    delay(1000);
  }

}

void loop() {


}

//
