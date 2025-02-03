#include "ultrasonic_int.h"

volatile uint16_t startCount;
volatile uint16_t endCount;
volatile uint16_t usTcnt;



//인터럽트 7번 사용
ISR(INT7_vect)
{
    if (ECHO_PORT & (1 << ECHO_PIN)) // Echo핀이 Rising이면
    {
        startCount = TCNT1; // 현재 값 저장

        EICRB &= ~(1 << ISC70); // falling edge로 변경
        EICRB |= (1 << ISC71);
    }
    else
    {
        endCount = TCNT1;
        usTcnt = endCount - startCount;

        EICRB |= (1 << ISC71) | (1 << ISC70); // Rising Edge 인터럽트 발생(INT3)
    }
}

void ultrasonicInit()
{
    TRTGGER_DDR |= (1 << TRIGGER_PIN); // 출력
    ECHO_DDR &= ~(1 << ECHO_PIN);      // 입력

    EICRB |= (1 << ISC71) | (1 << ISC70); // Rising Edge 인터럽트 발생(INT7)
    EIMSK |= (1 << INT7);                 // 인터럽트 7번 인에이블

    TCCR1B |= (1 << CS11) | (1 << CS10); // 64분주
}

void ultrasonicTrigger()
{
    TCNT1 = 0;

    TRIGGER_PORT &= ~(1 << TRIGGER_PIN); // low
    _delay_us(1);
    TRIGGER_PORT |= (1 << TRIGGER_PIN); // hi
    _delay_us(10);
    TRIGGER_PORT &= ~(1 << TRIGGER_PIN); // low
}

uint16_t ultrasonicDistance()
{
    uint16_t distance = (uint16_t)(usTcnt * 0.000004 * 34000) / 2; // 계산값 형변환
    return distance;
}





// //인터럽트 3번 사용
// ISR(INT3_vect)
// {
//     if (ECHO_PORT & (1 << ECHO_PIN)) // Echo핀이 Rising이면
//     {
//         startCount = TCNT1; // 현재 값 저장

//         EICRA &= ~(1 << ISC30); // falling edge로 변경
//         EICRA |= (1 << ISC31);
//     }
//     else
//     {
//         endCount = TCNT1;
//         usTcnt = endCount - startCount;

//         EICRA |= (1 << ISC31) | (1 << ISC30); // Rising Edge 인터럽트 발생(INT3)
//     }
// }

// void ultrasonicInit()
// {
//     TRTGGER_DDR |= (1 << TRIGGER_PIN); // 출력
//     ECHO_DDR &= ~(1 << ECHO_PIN);      // 입력

//     EICRA |= (1 << ISC31) | (1 << ISC30); // Rising Edge 인터럽트 발생(INT3)
//     EIMSK |= (1 << INT3);                 // 인터럽트 3번 인에이블

//     TCCR1B |= (1 << CS11) | (1 << CS10); // 64분주
// }

// void ultrasonicTrigger()
// {
//     TCNT1 = 0;

//     TRIGGER_PORT &= ~(1 << TRIGGER_PIN); // low
//     _delay_us(1);
//     TRIGGER_PORT |= (1 << TRIGGER_PIN); // hi
//     _delay_us(10);
//     TRIGGER_PORT &= ~(1 << TRIGGER_PIN); // low
// }

// uint16_t ultrasonicDistance()
// {
//     uint16_t distance = (uint16_t)(usTcnt * 0.000004 * 34000) / 2; // 계산값 형변환
//     return distance;
// }
