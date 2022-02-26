#include "includes.h"

// Set initial values of SCK and SDA pins
void i2c_init(void)
{	
    // Make SDA and SCK pins input initially
    SDA_DIR = 1;
    SCK_DIR = 1;
    
    // Write zero in output register of SDA and SCK pin
    SDA = 0;
    SCK = 0;
}

// I2C_Start sends start bit sequence
void i2c_start(void)
{
    SDA = 0;                            // Write zero in output register 
    SCK = 0;                            // of SDA and SCK pin
    
    Set_SCK_High;                       // Make SCK pin high
    Set_SDA_High;                       // Make SDA pin High
    __delay_us(HalfBitDelay);           // Half bit delay
    Set_SDA_Low;                        // Make SDA Low
    __delay_us(HalfBitDelay);           // Half bit delay
}

// I2C_Stop sends stop bit sequence
void i2c_stop(void)
{
    Set_SCK_Low;                        // Make SCK pin low
    
    __delay_us(HalfBitDelay / 2);       // Data pin should change it's value, 
                                        // when it is confirm that SCK is low
    Set_SDA_Low;                        // Make SDA pin low
	
    __delay_us(HalfBitDelay / 2);       // 1/4 bit delay
    Set_SCK_High;                       // Make SCK pin high
    __delay_us(HalfBitDelay / 2);       // 1/4 bit delay
    Set_SDA_High;                       // Make SDA high
    __delay_us(HalfBitDelay / 2);       // 1/4 bit delay
}

// Write_to I2C
void i2c_write(unsigned char DataByte)
{
    i2c_start();
    i2c_write_byte(I2C_PCF8574_ADDR << 1);
    i2c_write_byte(DataByte);
    i2c_stop();
}

// I2C_Write_Byte transfers one byte
void i2c_write_byte(unsigned char byte)
{
    unsigned char i;
    
    for(i = 0; i < 8; i++)              // Repeat for every bit
    {
        Set_SCK_Low;                    // Make SCK pin low
		
        __delay_us(HalfBitDelay / 2);   // Data pin should change it's value,
                                        // when it is confirm that SCK is low

        if((byte << i) & 0x80)          // Place data bit value on SDA pin
            Set_SDA_High;               // If bit is high, make SDA high
        else                            // Data is transferred MSB first
            Set_SDA_Low;                // If bit is low, make SDA low

        __delay_us(HalfBitDelay / 2);   // Toggle SCK pin
        Set_SCK_High;                   // So that slave can
        __delay_us(HalfBitDelay);       // latch data bit
    }
    
    // Get ACK from slave
    Set_SCK_Low;
    Set_SDA_High;
    __delay_us(HalfBitDelay);
    Set_SCK_High;
    __delay_us(HalfBitDelay);
}
