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

#include "timer.h"
#include <inttypes.h>

#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t sysTicks=0;

//
// initializes timer0 -- this function copied and pasted from sample code
// given in class
//
void init_Timer0( void )
{
    uint8_t csoMask = ( ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02) ); /* Calculate the mask for all CS0 bits */

//  TCCR0A = ( TCCR0A &  ( ~ csoMask ) ) | (1 << CS00 );               // Set prescaler to Processor clock/1
//  TCCR0A = ( TCCR0A &  ( ~ csoMask ) ) | (1 << CS01);                // Set prescaler to Processor clock/8
  TCCR0A = ( TCCR0A &  ( ~ csoMask ) ) | (1 << CS01) | (1 << CS00);  // Set prescaler to Processor clock/64
//  TCCR0A = ( TCCR0A &  ( ~ csoMask ) ) | (1 << CS02);                // Set prescaler to Processor clock/256
//  TCCR0A = ( TCCR0A &  ( ~ csoMask ) ) | (1 << CS02) | (1 << CS00);  // Set prescaler to Processor clock/1024

  TIFR0 = ( 1 << TOV0 );     		//Clear pending overflow
  TIMSK0 = TIMSK0 | ( 1 << TOIE0 );	//Enable overflow interrupts for Timer 0
}

//
// initialize timer1 -- virtually the same as timer0
//
void init_Timer1()
{
//    uint8_t csoMask = ( ( 1 << CS10 ) | ( 1 << CS11 ) | ( 1 << CS12) ); /* Calculate the mask for all CS1 bits */

    TCCR1A = (1<<COM1A1);// | (1<<COM1A0); // Set OC1A when upcounting, clear when downcounting
    TCCR1B = (1<<WGM13);        // Phase/Freq-correct PWM, top value = ICR1

//    TCCR1B = ( TCCR1B &  ( ~ csoMask ) ) | (1 << CS10 );               // Set prescaler to Processor clock/1
//  TCCR1B = ( TCCR1B &  ( ~ csoMask ) ) | (1 << CS11);                // Set prescaler to Processor clock/8
//  TCCR1B = ( TCCR1B &  ( ~ csoMask ) ) | (1 << CS11) | (1 << CS10);  // Set prescaler to Processor clock/64
//  TCCR1B = ( TCCR1B &  ( ~ csoMask ) ) | (1 << CS12);                // Set prescaler to Processor clock/256
//  TCCR1B = ( TCCR1B &  ( ~ csoMask ) ) | (1 << CS12) | (1 << CS10);  // Set prescaler to Processor clock/1024
}


void timer0_on()
{
    uint8_t csoMask = ( ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02) ); /* Calculate the mask for all CS0 bits */
    TCCR0A = ( TCCR0A &  ( ~ csoMask ) ) | (1 << CS01) | (1 << CS00);  // Set prescaler to Processor clock/64
}

void timer0_off()
{
    uint8_t csoMask = ( ( 1 << CS00 ) | ( 1 << CS01 ) | ( 1 << CS02) ); /* Calculate the mask for all CS0 bits */
    TCCR0A = TCCR0A & (~ csoMask);
}

void timer1_on()
{
//    uint8_t csoMask = ( ( 1 << CS10 ) | ( 1 << CS11 ) | ( 1 << CS12) ); /* Calculate the mask for all CS1 bits */
    TCCR1B |= (1<<0);             // start Timer1, prescaler(1)
}

void timer1_off()
{
//    uint8_t csoMask = ( ( 1 << CS10 ) | ( 1 << CS11 ) | ( 1 << CS12) ); /* Calculate the mask for all CS1 bits */
	//TCCR1A = 0;
    TCCR1B = 0;
}


//
// interrupt handler for timer0 overflow
// increments the system tick counter
//
ISR(TIMER0_OVF_vect)
{
    sysTicks++;

	//
	// TODO: calculate the exact value that should be used here
	//
    TCNT0 = 102;	//overflows should occur about ten times/second = 10Hz
					//the value was calculated through trial-and-error
					//by watching the tick count over a period of several minutes
}

ISR(TIMER1_OVF_vect)
{
	//do nothing
}
