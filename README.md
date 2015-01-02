Tock
====

An Arduino based nightstand alarm clock.

* Multiple alarms
* Accurate time with battery backup
* Configurable over Bluetooth Low Energy with [Tick](https://github.com/nickswalker/tick)

Independent Study Mentorship project for senior year at Communications Arts High School (2014).

### Hardware

The Tock is built around an Arduino-compatible board which is meant to be used in conjunction with a number
of cheap, widely available supporting modules. The PCB exposes all of the pins of the microcontroller, 
so it's easy to extend.

#### Bill of Materials

Part (Digi-Key #) | Quantity |
:---------------- | :-------:|
[Project PCB]()   | 1  
[HM-10 module](http://www.fasttech.com/products/0/10004051/1292002-ti-cc2540-bluetooth-40-ble-2540-transparent-serial) | 1
[Real time clock module]() | 1
[Adafruit I2C 4 digit seven segment display]() | 1
[Photoresistor]() | 1
[Female to male jumpers]() | 12
[Male header]()   | 2 rows of 40
[Female header]() | 1 row of 40
[]()              | 1

### Firmware

The C++ Arduino sketch uses three main global singletons to manage the hardware; an `IOHandler`, a 
`TimeKeeper` and `SensorHandler`. Hardware extensions should be coupled with additional methods on
these objects. Another singleton, the `AlarmsManager`, handles the interpretation of time events. A 
`Settings` class exposes methods to manipulate the EPROM for storing information between power cycles.

Various subclasses of the abstract `Command` class encapsulate the interpretation and execution of
commands recieved over the UART line from the Bluetooth Low Energy module. The `Command` class itself
contains a factory method for producing its concrete subclasses. Each of these has full access to the 
global singletons and can manipulate the state of the clock.




