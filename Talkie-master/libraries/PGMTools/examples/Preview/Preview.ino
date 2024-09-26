#include <PGMTools.h>

#define ArrSize 5
const PROGMEM uint8_t DataArr[ArrSize] = { 1, 2, 3, 4, 5 };

const PROGMEM uint8_t DataVal = 10;

void setup() {

  PGMArray<uint8_t, ArrSize> Arr(DataArr);

  PGMData<uint8_t> Val(DataVal);

  Serial.begin(9600);

  Serial.println(Val);

  for (uint8_t i = 0; i < 5; i++) {
    Serial.print(Arr[i]);
    Serial.print(" ");
  }

  Serial.println("\nEnd Setup");
}

void loop() {
}
