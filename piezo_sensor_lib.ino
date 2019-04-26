#include "Arduino.h"
#include "src/PiezoSensor/PiezoSensor.h"
#include "src/NumberBuffer/NumberBuffer.h"


PiezoSensor piezoSensor = PiezoSensor(A0);
const int LED_PIN = 8;
const int PIEZO_SPEAKER_PIN = 11;

NumberBuffer toneBuffer = NumberBuffer(20);

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  piezoSensor.loop();
  Serial.print("state ");
  Serial.print(piezoSensor.state);
  Serial.print(" | value ");
  Serial.println(piezoSensor.value);

  
  toneBuffer.add(map(piezoSensor.value, 0, 255, 0, 500));
  if (piezoSensor.state == PiezoSensor::OFF) {
    analogWrite(LED_PIN, 0);
    noTone(PIEZO_SPEAKER_PIN);
  } else {
    analogWrite(LED_PIN, piezoSensor.value);
    tone(PIEZO_SPEAKER_PIN, toneBuffer.average());
  }
  delay(1);
}
