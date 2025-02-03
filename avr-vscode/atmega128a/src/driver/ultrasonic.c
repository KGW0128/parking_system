#include "ultrasonic.h"

void timerInit()
{
    DDRD |= (1<<PORTD6);    //Trigger
    DDRD &= ~(1<<PORT7);    //Echo

    TCCR1B |=(1<<CS12) |(1<<CS10); //1024분주

}


void triggerPin()
{
    PORTD &=~(1<<PORTD6); //low 초기화
    _delay_us(1);
    PORTD |=(1<<PORTD6); //high 켜기
    _delay_us(10);
    PORTD &=~(1<<PORTD6); //low 초기화
   
}


uint8_t meanDistance()
{
    TCNT1 =0;
    while(!(PIND & (1<<PORTD7))) //high 까지 대기
    {
        if(TCNT1 > 65000)
        {
            return 0;
        }

    }

    TCNT1 = 0;
    while((PIND & (1<<PORTD7))) //low 까지 대기
    {
        if(TCNT1 > 65000)
        {
            TCNT1 = 0;
            break;
        }

    }

    //원위치 시키려 만든 변수(마이크로 세크)
    double pulseWidth = 1000000.0 * TCNT1 * 1024/16000000;

    return pulseWidth / 50;

}