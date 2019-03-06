#include <Arduino.h>
#include <nExtSP.h>

NEXTSP nextsp;

bool isMaster;

bool wasPressed;

void onCallback(byte* b,int length){
  for(auto i = 0; i< length; i++){
    //Serial.print(b[i]); //print receieved bytes
  }
  //Serial.println("");
  if(b[0] == 'a'){ //if a, turn led on
    digitalWrite(25,1);
  }else{
    digitalWrite(25,0);
  }
}

void setup() {
  wasPressed = false;
  Serial.begin(9600);
  Serial.println("started");
  pinMode(33, INPUT); //master / slave switch
  pinMode(25, OUTPUT); //led
  pinMode(26, INPUT); //button
  isMaster = digitalRead(33);

  nextsp.begin(isMaster,"43750697",&onCallback); // init espnext
}

void loop() {
    bool on = digitalRead(26); // if button is pressed
    if(on){
      if(wasPressed){
        nextsp.send((byte)'a');
        //Serial.println("on");
        wasPressed = false;
      }
    }else{
      if(!wasPressed){
        //Serial.println("off");
        nextsp.send((byte)'u');
        wasPressed = true;
      }
    }
  nextsp.update();
}

