#include "includes.h" 

void photoresistor_init(void)
{
    TRISA0 = 1;         // Make A0 input
    ANS0 = 1;           // Make A0 analog input
    
    ADCON0 = 0x01;      // Configure A/D Converter
    ADCON1 = 0x80;
}

int photoresistor_read(void)
{
    GO = 1;             // Start A/D Converter
    while(GO);          // Wait until stopped
    
    int value = (ADRESH << 8) + ADRESL;
    
    // From observations, i saw that the A/D Converter gives 1020 at minimum brightness and 5 at maximum brightness
    // So the following Normalization Formula derives
    return 100 - (value - 5) / 10.15;
}
