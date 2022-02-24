#include "includes.h"

void main(void) 
{
    const int delay_ms = 1000;
    
    TRISD7 = 0;
    
    while (1) 
    {
        RD7 = 1;
        __delay_ms(delay_ms);
        RD7 = 0;
        __delay_ms(delay_ms);
    }
        
    return;
}
