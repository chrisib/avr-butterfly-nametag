//
// Chris Iverach-Brereton 6800795
// 
//

#include <inttypes.h>
#include <avr/io.h>
#include "button.h"

//hysteresis values for each button
uint8_t centre_hist;
uint8_t up_hist;
uint8_t down_hist;
uint8_t left_hist;
uint8_t right_hist;

//is each button currently on?
uint8_t centreOn;
uint8_t upOn;
uint8_t downOn;
uint8_t leftOn;
uint8_t rightOn;

//
// initialize button input
//
void init_Buttons()
{
    // Init port pins
    // buttons are:
    //  centre: PINB4
    //  A       PINB6
    //  B       PINB7
    //  C       PINE2
    //  D       PINE3

    uint8_t pinB_mask = (1<<PINB4) | (1<<PINB6) | (1<<PINB7);
    uint8_t pinE_mask = (1<<PINE2) | (1<<PINE3);

    //clear the masked bits in the Data Direction registers (0=input)...
    DDRB = DDRB & (~pinB_mask);
    DDRE = DDRE & (~pinE_mask);

    //... and then set them to 1 in the PORT_ registers (1=enable pull-up)
    PORTB = PORTB | pinB_mask;
    PORTE = PORTE | pinE_mask;

	// enable AIN0, AIN1 input buffers (PE2/PE3)
    DIDR1 &= ~( (1<<AIN0D) | (1<<AIN1D) ); 

    //disable pin change interrupts
    EIMSK &= ~( (1<<PCIE1) | (1<<PCIE0) | (1<<PCINT0) );

    //set the hysteresis values to OFF_MIN
    centre_hist=BUTTON_OFF_MIN;
    up_hist=BUTTON_OFF_MIN;
    down_hist=BUTTON_OFF_MIN;
    left_hist=BUTTON_OFF_MIN;
    right_hist=BUTTON_OFF_MIN;

    //set button on/off flags to OFF
    centreOn=OFF;
    upOn=OFF;
    downOn=OFF;
    leftOn=OFF;
    rightOn=OFF;
}

//
// polls each button and sets its hysteresis values
// returns an 8-bit value giving the state of the buttons after debouncing:
// return & 1<<KEY_X == 1 if KEY_X is pressed
//                   == 0 if KEY_X is released (aka not pressed
//
uint8_t pollButtons()
{
    uint8_t retCode = 0x00;

    //
    // poll each button and debounce using hysteresis values
    // independent ifs because more than one can be pressed at once
    //
//////////////
    if(KEY_CENTRE_PRESS)
    {
        if(centre_hist<BUTTON_ON_MAX)
            centre_hist++;

        if(centre_hist>BUTTON_ON_MIN)
        {
            retCode |= 1<<KEY_CENTRE;
            centreOn=ON;
        }
    }
    else
    {
        if(centre_hist>BUTTON_OFF_MIN)
            centre_hist--;

        if(centre_hist<BUTTON_OFF_MAX)
            centreOn=OFF;
    }
//////////////
    if(KEY_UP_PRESS)
    {
        if(up_hist<BUTTON_ON_MAX)
            up_hist++;

        if(up_hist>BUTTON_ON_MIN)
        {
            retCode |= 1<<KEY_UP;
            upOn=ON;
        }
    }
    else
    {
        if(up_hist>BUTTON_OFF_MIN)
            up_hist--;

        if(up_hist<BUTTON_OFF_MAX)
            upOn=OFF;
    }
//////////////
    if(KEY_DOWN_PRESS)
    {
        if(down_hist<BUTTON_ON_MAX)
            down_hist++;

        if(down_hist>BUTTON_ON_MIN)
        {
            retCode |= 1<<KEY_DOWN;
            downOn=ON;
        }
    }
    else
    {
        if(down_hist>BUTTON_OFF_MIN)
            down_hist--;

        if(down_hist<BUTTON_OFF_MAX)
            downOn=OFF;
    }
//////////////
    if(KEY_LEFT_PRESS)
    {
        if(left_hist<BUTTON_ON_MAX)
            left_hist++;

        if(left_hist>BUTTON_ON_MIN)
        {
            retCode |= 1<<KEY_LEFT;
            leftOn=ON;
        }
    }
    else
    {
        if(left_hist>BUTTON_OFF_MIN)
            left_hist--;

        if(left_hist<BUTTON_OFF_MAX)
            leftOn=OFF;
    }
//////////////
    if(KEY_RIGHT_PRESS)
    {
        if(right_hist<BUTTON_ON_MAX)
           right_hist++;

        if(right_hist>BUTTON_ON_MIN)
        {
            retCode |= 1<<KEY_RIGHT;
            rightOn=ON;
        }
    }
    else
    {
        if(right_hist>BUTTON_OFF_MIN)
            right_hist--;

        if(right_hist<BUTTON_OFF_MAX)
            rightOn=OFF;
    }
//////////////
    return retCode;
}

//
// poll the buttons but perform no debouncing
// return is identical to pollButtons() (see above)
//
uint8_t pollButtons_NoDebounce()
{
    uint8_t retCode = 0x00;

    if(KEY_CENTRE_PRESS)
        retCode |= 1<<KEY_CENTRE;

    if(KEY_UP_PRESS)
        retCode |= 1<<KEY_UP;

    if(KEY_DOWN_PRESS)
        retCode |= 1<<KEY_DOWN;

    if(KEY_LEFT_PRESS)
        retCode |= 1<<KEY_LEFT;

    if(KEY_RIGHT_PRESS)
        retCode |= 1<<KEY_RIGHT;

    return retCode;
}
