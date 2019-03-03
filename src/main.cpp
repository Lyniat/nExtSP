#include <Arduino.h>
#include <Next.h>

ESPNext *next;

void onCallback(byte b){
  Serial.println(b);
}

void setup() {
  Serial.begin(9600);
  Serial.println("started");
  next = new ESPNext(33,&onCallback);
}

void loop() {
  next->update();
}

