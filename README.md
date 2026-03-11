# AVR Butterfly Nametag

This is a copy of an _ancient_ Realtime Systems project I worked on during my undergrad. It's
likely of no interest to anyone who isn't me, but I wanted to preserve it. And just in case it's
helpful to anyone in the future, I've made it public.

The project itself is a simple nametag made using the AVR Butterfly and uses the 5-way joystick
to act as a primitive synthesizer.

[![Demo Video](http://img.youtube.com/vi/oGad-J9R6nw/0.jpg)](http://www.youtube.com/watch?v=oGad-J9R6nw  "AVR Butterfly Nametag Demo")

## Prerequisites

You will need `avr-gcc` and `avrdude` installed on your system to build & deploy this project.
These are available on Ubuntu, and likely other operating systems.

```bash
sudo apt-get install gcc-avr avr-libc avrdude
```

## Building

To build, `cd` into the project folder and run `make`. `make clean` will clean up any built
artifacts in the directory.

## Flashing

To write the binary after building it, `cd` into the project folder and run `make program`.

You must have your AVR Butterfly's UART connected to your computer's serial port. (A
USB-to-serial adapter is likely needed unless you've got some _unique_ hardware.)

When `avrdude` prompts you, click the AVR Butterfly's joystick "in" to enter the bootloader.
Once the write is complete you may need to manually reset the board. Click the joystick "up" to
start the program.

## Modifying

To change the name displayed on the nametag, since as far as I know there isn't anyone else in
the world with my exact name, edit `main.c` to change the string.

```c
LCD_puts("YOUR NAME HERE", TRUE);   // display some text (see lcd_functions.h)
```

The second parameter will control whether or not the text scrolls. If your name is sufficiently
short you can turn it off. Otherwise scrolling is necessary to see the whole string.

To change the notes that play when you use the joystick as an "instrument" choose the notes
edit the main loop in `main.c` to choose different notes. Notes are defined in `speaker.h`:

```c
if(buttonState & (1 << KEY_UP))
    playNote(C0,VOLUME);
else if(buttonState & (1 << KEY_RIGHT))
    playNote(D0,VOLUME);
else if(buttonState & (1 << KEY_DOWN))
    playNote(E0,VOLUME);
else if(buttonState & (1 << KEY_LEFT))
    playNote(G0,VOLUME);
else if(buttonState & (1 << KEY_CENTRE))
    playNote(A0,VOLUME);
else
    playNote(0,0);
```

The `else` case should always be `(0, 0)` to turn the speaker off when nothing is pressed.
