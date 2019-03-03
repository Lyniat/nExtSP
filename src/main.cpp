#include <Arduino.h>
#include <nExtSP.h>

ESPNext *next;

bool isMaster;

void onCallback(byte* b,int length){
  for(auto i = 0; i< length; i++){
    Serial.print(b[i]); //print receievd bytes
  }
  Serial.println("");
  if(b[0] == 'a'){ //if a, turn led on
    digitalWrite(25,1);
  }else{
    digitalWrite(25,0);
  }
}

void setup() {
  Serial.begin(9600);
  Serial.println("started");
  pinMode(33, INPUT); //master / slave switch
  pinMode(25, OUTPUT); //led
  pinMode(26, INPUT); //button
  isMaster = digitalRead(33);

  next = new ESPNext(isMaster,"43750697",&onCallback); // init espnext
}

void loop() {
  if(isMaster){
    bool on = digitalRead(26); // if button is pressed
    if(on){
      next->send((byte)'a');
      Serial.println("on");
    }else{
      Serial.println("off");
      next->send((byte)'u');
    }
  }else{
    
  }
  next->update();
}

