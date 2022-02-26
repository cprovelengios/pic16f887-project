#ifndef __I2C_H
#define __I2C_H

// Define i2c pins
#define SDA         RA1                 // Data pin for i2c
#define SCK         RA2                 // Clock pin for i2c
#define SDA_DIR     TRISA1              // Data pin direction
#define SCK_DIR     TRISA2              // Clock pin direction

// Define i2c speed
#define I2C_SPEED       400             // kbps 
#define HalfBitDelay    500/I2C_SPEED   // usec

// Define macros
#define Set_SDA_Low     SDA_DIR = 0
#define Set_SDA_High    SDA_DIR = 1     // When i make a pin as input, it becomes high automatically because there is a pull up resistor
#define Set_SCK_Low     SCK_DIR = 0
#define Set_SCK_High    SCK_DIR = 1

// Function Declarations
void i2c_init(void);
void i2c_start(void);
void i2c_stop(void);
void i2c_write(unsigned char);
void i2c_write_byte(unsigned char);

#endif
