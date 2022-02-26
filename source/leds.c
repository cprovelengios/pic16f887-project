#include "includes.h"

int count = 0;


void leds_init(void)
{
    // Configuration for blinking led
    TRISD7 = 0;             // Make RD7 output
    RD7 = 0;                // Led1 OFF

    // t = prescaler / (FOSC / 4) * (256 - value)
    OPTION_REG &= 0xC0;     // Configure TIMER0 MODULE
    OPTION_REG |= 0x02;
    TMR0 = 131;             // Load the timer value for 1ms delay
    T0IE = 1;               // Enable the Timer0 interrupt
    
    GIE = 1;                // Global Interrupt Enable 
}

void interrupt isr(void)
{  
    if(T0IF == 1)                   // Check TIMER0 Interrupt Flag bit
    {
        TMR0 = 132;                 // Load 132 instead of 131 because it needs two instruction Cycles to start incrementing TIMER0
        T0IF = 0;                   // Clear the Flag bit
        
        if(count >= 1000)          // 1ms * 1000 = 1sec
        {
            count = 0;
            RD7 = !RD7;             // Led1 blink
        }
        else
            count++;
    }
}
