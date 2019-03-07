# nExtSP
##### nower than ESP-Now
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![HitCount](http://hits.dwyl.io/Lyniat/nExtSP.svg)](http://hits.dwyl.io/Lyniat/nExtSP)

## Why?
ESP-Now is nice, but when you need a really simple peer-to-peer connection between two ESP32, it's still too complicated.<br>
nExtSP solves this problem by using only four lines of code!

```c++
  1. NEXTSP nextsp;
  2. nextsp.begin(isMaster,"43750697",&onCallback); // init espnext
  3. nextsp.send("test");
  4. nextsp.update();
```

## How?

```c++
  #include <nExtSP.h>

  NEXTSP nextsp;
  
  void onCallback(byte* b,int length){
  //...
  }
  
  void setup(){
  //            boolean, if esp32 is master or slave
  //              |      choose a unique id for every pair
  //              |         |        register callback function
  //              v         v            v
  //...
  nextsp.begin(isMaster,"43750697",&onCallback);
  //...
  }
  
  void loop(){
  //...
  nextsp.send("test");
  //...
  nextsp.update();
  //...
  }
```

See also example code in repository.

## Contribution
Contribution is always welcome :)

## License
* MIT
* by [Laurin Muth](https://hci.ur.de/people/laurin_muth)
