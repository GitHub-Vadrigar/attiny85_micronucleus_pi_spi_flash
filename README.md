# Digispark (ATtiny85) Flashing with rpi 4 GPIO

## Connect Raspberry Pi 4 to Digispark:
### Digispark pinout
<img src="https://europe1.discourse-cdn.com/arduino/optimized/4X/7/9/2/792251f6b79970904de17bc51383f200771bc306_2_1000x758.png" 
style="width: 50%">

### Raspberry Pi 4 GPIO pinout
<img src="https://www.raspberrypi.com/documentation/computers/images/GPIO-Pinout-Diagram-2.png" 
style="width: 50%"><br>

### rpi 4 GPIO to Digispark connection 

<p>
    pin 4 (5V)&emsp;> &nbsp; 5V <br>
    pin 6 (GND)&emsp;> &nbsp; GND <br>
    pin 15 (GPIO 22) &nbsp; > &nbsp; PB5<br>
    pin 19 (MOSI)&emsp; > &nbsp; PB0 <br>
    pin 21 (MISO)&emsp; > &nbsp; PB1 <br>
    pin 23 (SCLK)&emsp; > &nbsp; PB2 <br>
</p>


## Enable SPI on Raspberry Pi 4
* `sudo raspi-config`
* Select: Interfacing Options > SPI <br>
(You don't need to reboot your Raspberry Pi)


## Install Flashing Software
`sudo apt-get install bison automake autoconf flex git gcc`\
`sudo apt-get install gcc-avr binutils-avr avr-libc`<br><br>
`cd ~`\
`git clone https://github.com/kcuzner/avrdude`\
`cd avrdude/avrdude`\
`./bootstrap && ./configure && sudo make install`<br><br>
`cd ~`\
`git clone https://github.com/WiringPi/WiringPi`\
`cd WiringPi`\
`./build` <br>

## Flashing Digispark with LED blink program
`cd ~`\
`git clone https://github.com/edvirs/attiny85_blink`\
`cd attiny85_blink`<br>
#### To flash, simply use this line:
`make install`
#### The output should look like this:
```
/usr/bin/avr-gcc -g -Os -Wall -mcall-prologues -mmcu=attiny85 blink.c -o blink
/usr/bin/avr-objcopy -R .eeprom -O ihex blink blink.hex
rm -f blink
sudo gpio -g mode 22 out
sudo gpio -g write 22 0
sudo /usr/local/bin/avrdude -p t85 -P /dev/spidev0.0 -c linuxspi -b 10000 -U flash:w:blink.hex

avrdude: AVR device initialized and ready to accept instructions

Reading | ################################################## | 100% 0.01s

avrdude: Device signature = 0x1e930b
avrdude: NOTE: "flash" memory has been specified, an erase cycle will be performed
         To disable this feature, specify the -D option.
avrdude: erasing chip
avrdude: reading input file "blink.hex"
avrdude: input file blink.hex auto detected as Intel Hex
avrdude: writing flash (144 bytes):

Writing | ################################################## | 100% 0.56s

avrdude: 144 bytes of flash written
avrdude: verifying flash memory against blink.hex:
avrdude: load data flash data from input file blink.hex:
avrdude: input file blink.hex auto detected as Intel Hex
avrdude: input file blink.hex contains 144 bytes
avrdude: reading on-chip flash data:

Reading | ################################################## | 100% 0.53s

avrdude: verifying ...
avrdude: 144 bytes of flash verified

avrdude: safemode: Fuses OK (E:FE, H:DF, L:F1)

avrdude done.  Thank you.

sudo gpio -g write 22 1

```
#### And the LED should blink every 250ms
Obviously, you can write your own C code for ATtiny85 and flash it,\
just don't forger to change the TARGET variable in the Makefile
## Resources:
* [Programming the ATtiny85 From Raspberry Pi](https://www.instructables.com/Programming-the-ATtiny85-from-Raspberry-Pi/)
* [Bare Metal Programming: ATtiny85](https://medium.com/@bradford_hamilton/bare-metal-programming-attiny85-22be36f4e9ca)