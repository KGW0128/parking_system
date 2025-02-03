#include "pwm16.h"


void pwm16Init()
{
    DDRE |= (1<<PORTE3);    //OC3A past PWM output(출력이 나감)
   
    //64분주, past PWM, 비반전mode
    TCCR3A |= (1<<COM3A1) | (1<<WGM31);
    TCCR3B |= (1<<WGM33) |(1<<WGM32)|(1<<CS31)|(1<<CS30);


    //계산된 TOP값(50hz, 20ms)
    ICR3 = 4999;
}

