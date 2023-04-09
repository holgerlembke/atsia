# All The Same I2C Address

Preface: this is pure Arduino code. Nothing changed, no tricks, no false bottom. 

## The other day

The other day I was playing around with an PCF8577 based LC-Display. As usual, this LCD stuff is strange. But what puzzled me most was the idea that the PCF8577 only has one (non selectable) I2C address. And that by using an index number within the command bytes send to it, one of multipe PCF8577s can be addressed.

What?

I had to repeat it to myself: Multiple devices with the same bus address select themself by data send to all these devices. That works? Really?

## I'm lucky fella with lots of ATtinys!

A very trusted ebay seller shipped some ATtiny85 to me. That was ages ago, but I still have some left:

![Atsia](https://raw.githubusercontent.com/holgerlembke/atsia/main/media/attinylegs.jpg)

As you can see, the 131 km between him and me was a way harder journey than most Shenzen stuff has had. But I disgress.

## Yes!

![Atsia](https://raw.githubusercontent.com/holgerlembke/atsia/main/media/atsiammedia.gif)

This mess of wires is one Arduino Uno and four ATtiny 85.

The ATtiny85 are set up the following way:

```
                              +---v---+
                          PB5 |1     8| VCC
           Input+ID0        3 |2     7| 2  SCL
                 ID1        4 |3     6| 1  LED
                          GND |4     5| 0  SDA
                              +-------+
  Command interface
        76543210
        00SLRIAA

    AA ID
    L  1: is LED command
    S  x: state of LED
```
![Atsia](https://raw.githubusercontent.com/holgerlembke/atsia/main/media/atsiaimg.jpg)

Wires:
* red/black: Vcc,Vdd
* yellow: LED
* blue: ID-selector by pulling down to Vdd
* white: SCL
* green: SDA

ID0/ID1 are used to select the internal ID. All ATtiny85 share the same I2C address, 0x42 in this case. This can be verified with a simple I2C bus scanner:

![Atsia](https://raw.githubusercontent.com/holgerlembke/atsia/main/media/atsiaserver.png)

## atsiaClient

A simple command interface was designed. Bit 0+1 select the ID (0..3). ID is set by the external pins at boot time and for verification, the Tinys blink it out at boot time Bit 4 controles the access to the LED, bit 5 sets/clears the LED. Simple stuff.

## atsiaMaster

Not much special, too. Just do a I2C bus scan and than blinky the LEDs.

## ATtiny85

I use https://github.com/SpenceKonde/ATTinyCore .

## Conclusion

Render me surprised.
