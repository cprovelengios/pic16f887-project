#include "includes.h"

void main(void) 
{
    i2c_init();
    lcd_init();
    leds_init();
   
    lcd_move_cursor(1, 3);
    lcd_write_string("PIC16F887_CP");
    
    while(1) {}
    
    return;
}
