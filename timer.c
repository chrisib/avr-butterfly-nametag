//
// Chris Iverach-Brereton 6800795
// timer functions used for A1
//

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
