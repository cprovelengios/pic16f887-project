#include "includes.h"

int count1 = 0;             // Used to count 1 sec
int count2 = 0;             // Used to count 50 ms

void leds_init(void)
{
    // Configuration for blinking led
    TRISD7 = 0;             // Make RD7 output
    RD7 = 0;                // Led1 OFF

    // t = prescaler / (FOSC / 4) * (256 - value)
    OPTION_REG &= 0xC0;     // Configure TIMER0 MODULE
    OPTION_REG |= 0x02;     // prescaler: 8
    TMR0 = 131;             // Load the timer value for 1 ms delay
    T0IE = 1;               // Enable the Timer0 interrupt
    
    // Configuration for push-button led
    TRISD6 = 0;             // Make RD6 output
    RD6 = 0;                // Led2 OFF
    
    TRISB5 = 1;             // Make RB5 input
    ANS13 = 0;              // Make RB5 Digital I/O
    nRBPU = 0;              // Enable pull-ups at Port B
    IOCB5 = 1;              // Interrupt-on-change enabled at RB5
    RBIE = 1;               // Enable the PORTB change interrupt
    
    GIE = 1;                // Global Interrupt Enabled
}

void interrupt isr(void)
{  
    if(T0IF == 1)                   // Check TIMER0 Interrupt Flag bit
    {
        TMR0 = 132;                 // Load 132 instead of 131 because it needs two instruction Cycles to start incrementing TIMER0
        T0IF = 0;                   // Clear the Flag bit
        
        if(count1 >= 1000)          // 1 ms * 1000 = 1 sec
        {
            count1 = 0;
            RD7 = !RD7;             // Led1 blink
        }
        else
            count1++;
        
        if(RD6)                     // Check if Led2 is ON
        {
            if(count2 >= 50)        // 1 ms * 50 = 50 ms
            {
                count2 = 0;
                
                if(RB5)             // Check every 50 ms if the button is released
                {
                    RD6 = 0;        // Led2 OFF
                    RBIE = 1;       // Enable the PORTB change interrupt
                }
            }
            else
                count2++;
        }
    }
    
    if(RBIF == 1 && RBIE == 1)      // Check PORTB Change Interrupt Flag bit and if interrupts are enabled
    {
        RD6 = 1;                    // Led2 ON
        RBIF = 0;                   // Clear the Flag bit
        RBIE = 0;                   // Disable the PORTB change interrupt
    }
}
