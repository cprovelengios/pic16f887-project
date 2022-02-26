#include "includes.h"

void main(void) 
{
    int value;
    
    i2c_init();
    lcd_init();
    leds_init();
    photoresistor_init();
   
    lcd_move_cursor(1, 3);
    lcd_write_string("PIC16F887_CP");
    
    while(1)
    {
        lcd_clear(2, 2, 15);
        lcd_write_string("BRIGHTNESS: ");
        
        while((value = photoresistor_read()) < 86)
        {
            lcd_clear(2, 14, 3);
            lcd_write_number(value);
            __delay_ms(250);
        }
        
        lcd_clear(2, 2, 15);
        lcd_write_string("WARNING BR: ");
        
        while((value = photoresistor_read()) > 85)
        {
            lcd_clear(2, 14, 3);
            lcd_write_number(value);
            __delay_ms(250);
        }
    }
    
    return;
}
