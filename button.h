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

#ifndef BUTTON_H
#define BUTTON_H

#include <inttypes.h>

//macro "functions" to read if a button is down or not
#define KEY_CENTRE_PRESS   (!(PINB & (1<<PINB4)))
#define KEY_UP_PRESS       (!(PINB & (1<<PINB6)))
#define KEY_DOWN_PRESS     (!(PINB & (1<<PINB7)))
#define KEY_LEFT_PRESS     (!(PINE & (1<<PINE2)))
#define KEY_RIGHT_PRESS    (!(PINE & (1<<PINE3)))

#define ON 1
#define OFF 0

#define KEY_CENTRE  1
#define KEY_UP      2
#define KEY_DOWN    3
#define KEY_LEFT    4
#define KEY_RIGHT   5

//button hysteresis limits
//0-4 considered to be OFF (not pressed)
//12-16 considered to be ON (pressed)
#define BUTTON_OFF_MIN  0
#define BUTTON_OFF_MAX  2
#define BUTTON_ON_MIN   3
#define BUTTON_ON_MAX   5

//hysteresis values for all buttons
//extern uint8_t centre_hist;
//extern uint8_t up_hist;
//extern uint8_t down_hist;
//extern uint8_t left_hist;
//extern uint8_t right_hist;

//extern uint8_t centreOn;
//extern uint8_t upOn;
//extern uint8_t downOn;
//extern uint8_t leftOn;
//extern uint8_t rightOn;

void init_Buttons(void);

uint8_t pollButtons(void);
uint8_t pollButtons_NoDebounce(void);

#endif
