/**
Software License Agreement (BSD)

\authors   Chris Iverach-Brereton <ve4cib@gmail.com>
\copyright Copyright (c) 2012, 2026 Chris Iverach-Brereton, All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that
the following conditions are met:
 * Redistributions of source code must retain the above copyright notice, this list of conditions and the
   following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
   following disclaimer in the documentation and/or other materials provided with the distribution.
 * Neither the name of Clearpath Robotics nor the names of its contributors may be used to endorse or promote
   products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WAR-
RANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, IN-
DIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <avr/io.h>
#include <avr/iom169.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/sleep.h>
#include <inttypes.h>

#include "main.h"
#include "lcd_functions.h"
#include "lcd_driver.h"
#include "button.h"
#include "speaker.h"
#include "timer.h"

#define VOLUME 1000

int main()
{
    LCD_Init(); // initialize the LCD (see lcd_driver.h)
    init_Speaker();
    init_Buttons();

    sei();      // enable interrupts (avr/interrupt.h)

    LCD_puts("Chris I-B", TRUE);   // display some text (see lcd_functions.h)

    // main should never, EVER exit
#ifdef DEBUG
    char buffer [8];
#endif
    uint8_t buttonState;
    timer1_on();
    for(;;)
    {
        buttonState = pollButtons_NoDebounce();
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
#ifdef DEBUG
        sprintf(buffer,"%d",buttonState);
        LCD_puts(buffer,FALSE);
#endif
    }

    return 0;
}
