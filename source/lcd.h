#ifndef __I2CLCD_H
#define __I2CLCD_H

// LCD bits locations
#define LOC_RS          0
#define LOC_RW          1
#define LOC_EN          2
#define LOC_DATA        4
#define WID_DATA        4

// LCD commands
#define DIS_CLR         0x01
#define DIS_ENTRY_MODE  0x06
#define DIS_ON_CUR_ON   0x0E
#define DIS_ON_CUR_OFF  0x0C
#define DIS_SET_4B2L    0x28
#define DIS_4_BIT1      0x32
#define DIS_4_BIT2      0x33
#define DIS_1ROW        0x80
#define DIS_2ROW        0xC0
#define DIS_CUR_RIGHT   0x14
#define DIS_CUR_LEFT    0x10

// LCD options
#define OPT_CMD         0
#define OPT_DATA        1

// Function Declarations
void lcd_init(void);
unsigned char lcd_update_word(unsigned char, unsigned char, unsigned char, unsigned char);
void lcd_set_rs(void);
void lcd_clear_rs(void);
void lcd_set_rw(void);
void lcd_clear_rw(void);
void lcd_set_en(void);
void lcd_clear_en(void);
void lcd_set_data(unsigned char);
void lcd_toogle_en(void);
void lcd_write_byte(unsigned char, unsigned char);
void lcd_write_string(char *);
void lcd_write_number(unsigned int);
void lcd_write_register(unsigned char);
void lcd_clear(unsigned char, unsigned char, unsigned char);
void lcd_clear_all(void);
void lcd_move_cursor(unsigned char, unsigned char);

#endif
