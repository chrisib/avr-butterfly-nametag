//
// Chris Iverach-Brereton 6800795
// Header file for button functions used in A1
//

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
