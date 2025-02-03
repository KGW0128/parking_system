#include "rgb_led.h"

void set_color(int red, int green, int blue)
{
    OCR1_R = red;
    OCR1_G = green;
    OCR1_B = blue;
}


void rgb_init()
{
    // Fast PWM 8bit
    // WGM13(0), WGM12(1), WGM11(0), WGM10(1)
    // COM1A1/COM1B1/COM1C1 : 1, COM1A0/COM1B0/COM1C0 : 0
    DDRB = 0xff;
    TCCR1A |= (1<<WGM10) | (1<<COM1A1) | (1<<COM1B1) | (1<<COM1C1);
    TCCR1B |= (1<<WGM12) | (1<<CS11);
    set_color(0, 0, 0);
}