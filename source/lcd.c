#include "includes.h" 

// Set P3 high to turn on the backlight. P3 is not connected to the LCD
unsigned char lcd_word = 0x08;

void lcd_init(void)
{
    lcd_write_byte(OPT_CMD, DIS_4_BIT2);
    lcd_write_byte(OPT_CMD, DIS_4_BIT1);
    lcd_write_byte(OPT_CMD, DIS_SET_4B2L);
    lcd_write_byte(OPT_CMD, DIS_ON_CUR_OFF);
    lcd_write_byte(OPT_CMD, DIS_CLR);
    lcd_write_byte(OPT_CMD, DIS_ENTRY_MODE);
}

// A function for updating a register field
unsigned char lcd_update_word(unsigned char reg_val, unsigned char field_loc, unsigned char field_width, unsigned char field_val)
{
    unsigned char mask = ~(((1 << field_width) - 1) << field_loc);  // Create the mask
    reg_val = reg_val & mask;                                       // Clear the field to be updated
    return reg_val | (field_val << field_loc);                      // Update that field and return the new value
}

void lcd_set_rs(void)
{
    lcd_word = lcd_update_word(lcd_word, LOC_RS, 1, 1);
}

void lcd_clear_rs(void)
{
    lcd_word = lcd_update_word(lcd_word, LOC_RS, 1, 0);
}

void lcd_set_rw(void)
{
    lcd_word = lcd_update_word(lcd_word, LOC_RW, 1, 1);
}

void lcd_clear_rw(void)
{
    lcd_word = lcd_update_word(lcd_word, LOC_RW, 1, 0);
}

void lcd_set_en(void)
{
    lcd_word = lcd_update_word(lcd_word, LOC_EN, 1, 1);
    i2c_write(lcd_word);
}

void lcd_clear_en(void)
{
    lcd_word = lcd_update_word(lcd_word, LOC_EN, 1, 0);
    i2c_write(lcd_word);
}

void lcd_set_data(unsigned char data)
{
    lcd_word = lcd_update_word(lcd_word, LOC_DATA, WID_DATA, data);
}

void lcd_toogle_en(void)
{
    lcd_set_en();
    lcd_clear_en();
}

void lcd_write_byte(unsigned char option, unsigned char data)
{
    if(option)
        lcd_set_rs();           // LCD data mode
    else
        lcd_clear_rs();         // LCD command mode
    
    lcd_set_data(data >> 4);
    lcd_toogle_en();
        
    lcd_set_data(data & 0x0F);
    lcd_toogle_en();
}

void lcd_write_string(char *string)
{
    while(*string)
        lcd_write_byte(OPT_DATA, *string++);
}

void lcd_write_number(unsigned int number)
{
    int i = 0, j = 0;
    char rev_str[5];
    char str[6];
    
    if(number)
    {
        while(number > 0)
        {
            int a = number % 10;
            rev_str[i++] = a | '0';
            number /= 10;
        }

        i--;

        while(i >= 0)
           str[j++] = rev_str[i--]; 
    }
    else
        str[j++] = '0';
   
    str[j] = '\0';
    
    for(i = 0; i < j; i++)
        lcd_write_byte(OPT_DATA, str[i]);
}

void lcd_write_register(unsigned char number)
{
    int i;
    
    for(i = 7; i >= 0; i--)
        lcd_write_byte(OPT_DATA, ((number >> i) & 0x01) | '0');
}

void lcd_clear(unsigned char row, unsigned char column, unsigned char number)
{
    int i;
    
    lcd_move_cursor(row, column);
    
    for(i = 0; i < number; i++)
        lcd_write_string(" ");
    
    lcd_move_cursor(row, column);
}

void lcd_clear_all(void)
{
    lcd_write_byte(OPT_CMD, DIS_CLR);
}

void lcd_move_cursor(unsigned char row, unsigned char column)
{
    int i;
    
    if(row == 1)
        lcd_write_byte(OPT_CMD, DIS_1ROW);
    else
        lcd_write_byte(OPT_CMD, DIS_2ROW);
        
    for(i = 1; i < column; i++)
        lcd_write_byte(OPT_CMD, DIS_CUR_RIGHT);
}
