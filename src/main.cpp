#include <Arduino.h>
#include <Next.h>

ESPNext *next;

bool isMaster;

void onCallback(byte* b,int length){
  for(auto i = 0; i< length; i++){
    Serial.print((char)b[i]);
  }
  Serial.println("");
}

void setup() {
  Serial.begin(9600);
  Serial.println("started");
  pinMode(33, INPUT);
  isMaster = digitalRead(33);

  next = new ESPNext(isMaster,"43750697",&onCallback);
}

void loop() {
  if(isMaster){
    next->send("I am sending master!");
  }else{
    next->send("I am sending client!");
  }
  next->update();
}

