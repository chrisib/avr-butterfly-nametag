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
