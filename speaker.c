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
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <inttypes.h>

#include "speaker.h"
#include "timer.h"

#include "main.h"
#include "button.h"

//an array of note_t structs defining the tone and duration of notes in the chime sound
#define MAX_NOTES 132
note_t chime[MAX_NOTES]; //= { { note : B1, duration : 50}, ;

uint8_t volume;

//
// initialize the piezo-electric speaker
//
void init_Speaker()
{
	uint8_t i;


	// set pin B5 as output, with high initial value
	uint8_t pinB_mask = (1<<PINB5);

	volume=80;		//set the volume to a default value

    //set the masked bits in the Data Direction register (1=output)...
    DDRB = DDRB | pinB_mask;

    //... and then set them to 1 in the PORT_ registers (1=output high)
    PORTB = PORTB | pinB_mask;

	//
	// the following code was copied-and-pasted from sound.c, provided as sample code in class in BF-GCC
	//
    TCCR1A = (1<<COM1A1);// | (1<<COM1A0); // Set OxC1A when upcounting, clear when downcounting
    TCCR1B = (1<<WGM13);        // Phase/Freq-correct PWM, top value = ICR1

	init_Timer1();				//initialize Timer1 (set to phase-correct PWM mode)

    OCR1AH = 0;        // Set a initial value in the OCR1A-register
    OCR1AL = volume;   // This will adjust the volume on the buzzer, lower value => higher volume

}

//
// play a simple series of tones
//
void playNote(uint16_t pitch, uint16_t volume)
{
    OCR1AH = 0;        // Set a initial value in the OCR1A-register
    OCR1AL = volume;   // This will adjust the volume on the buzzer, lower value => higher volume

    ICR1H = pitch >> 8;
    ICR1L = pitch & 0xff;
}
