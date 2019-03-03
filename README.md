# nExtSP
##### nower than ESP-Now
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![HitCount](http://hits.dwyl.io/Lyniat/nExtSP.svg)](http://hits.dwyl.io/Lyniat/nExtSP)

## !!!
This library will be changed in the next few days (of 03.03.19).
So please keep in mind, that your code might break!

## Why?
ESP-Now is nice, but when you need a really simple peer-to-peer connection between two ESP32, it's still too complicated.<br>
ESP-Now solves this problem by using only four lines of code!

```c++
  1. ESPNext *next;
  2. next = new ESPNext(isMaster,"43750697",&onCallback);
  3. next->send("test");
  4. next->update();
```

## How?

```c++
  //                  boolean, if esp32 is master or slave
  //                   |      choose a unique id for every pair
  //                   |         |        register callback function
  //                   v         v            v
  ...
  next = new ESPNext(isMaster,"43750697",&onCallback);
  ...
```

See also example code in repository.

## Contribution
Contribution is always welcome :)

## License
* MIT
* by [Laurin Muth](https://hci.ur.de/people/laurin_muth)
