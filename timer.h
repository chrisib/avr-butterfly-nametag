//
// Chris Iverach-Brereton 6800795
// header file for timer utilities used in A1
//

#ifndef TIMER_H
#define TIMER_H

#define TIMER0_FREQ	10	//timer0 has an interrupt frequency of 10Hz

#include <inttypes.h>

volatile extern uint16_t sysTicks;

void init_Timer0(void);
void init_Timer1(void);

void timer0_on(void);
void timer0_off(void);

void timer1_on(void);
void timer1_off(void);

#endif
