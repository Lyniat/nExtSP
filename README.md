# nExtSP
##### nower than ESP-Now
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## Why?
ESP-Now is nice, but when you need a really simple peer-to-peer like connection between two ESP32, it's still too complicated.<br>
nExtSP solves this problem by using only four lines of code!

```c++
  1. NEXTSP nextsp;
  2. nextsp.begin(isServer,"43750697",&onCallback);
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
  //            boolean, if esp32 is server or client
  //              |      choose a unique id for every pair
  //              |         |        register callback function
  //              v         v            v
  //...
  nextsp.begin(isServer,"43750697",&onCallback);
  //...
  }
  
  void loop(){
  //...
  nextsp.send("test");
  //...
  nextsp.update(); // call once every loop.
  //...
  }
```

See also example code in repository.

## License
* MIT
* by [Laurin Muth](https://hci.ur.de/people/laurin_muth)
