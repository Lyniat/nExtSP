#include <Arduino.h>
#include <Next.h>

ESPNext *next;

void setup() {
  Serial.begin(9600);
  Serial.println("started");
  next = new ESPNext(33);
}

void loop() {
  next->update();
}