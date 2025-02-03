#include "uart1.h"
#include "led.h"

// 출력 스트림 설정 <stdio.h> 에 있는 표준 입출력임
FILE OUTPUT_1 = FDEV_SETUP_STREAM(uart1_Read_Transmit, NULL, _FDEV_SETUP_WRITE);

char rxBuff_1[100] = {0}; // 수신버퍼
volatile uint8_t rxFlag_1 = 0;

uint8_t systemState = 2;

ISR(USART1_RX_vect) // 수신 인터럽트 핸들러
{
    static uint8_t rxHead = 0; // 수신된 데이터의 인덱스
    uint8_t rxData = UDR1;

    // uart1_Write_Transmit(rxData);

    LED led;
    led.port = &PORTB;
    led.pin = 0;
    ledInit(&led);

    if (rxData == 'A') // 입력문자가 A일 때 led킴
    {
        // ledOn(&led);
        // strcpy(rxBuff_1, "LED ON\n");

        uart1_Read_Transmit('S');
        uart1_Read_Transmit('y');
        uart1_Read_Transmit('s');
        uart1_Read_Transmit('t');
        uart1_Read_Transmit('e');
        uart1_Read_Transmit('m');
        uart1_Read_Transmit(' ');
        uart1_Read_Transmit('L');
        uart1_Read_Transmit('o');
        uart1_Read_Transmit('c');
        uart1_Read_Transmit('k');
        uart1_Read_Transmit('\n');

        // uart1_Write_Transmit('L');
        // uart1_Write_Transmit('E');
        // uart1_Write_Transmit('D');
        // uart1_Write_Transmit(' ');
        // uart1_Write_Transmit('O');
        // uart1_Write_Transmit('N');
        // uart1_Write_Transmit('\n');

        systemState = 1;
    }
    else if (rxData == 'B')
    {
        //ledOff(&led);

        uart1_Read_Transmit('S');
        uart1_Read_Transmit('y');
        uart1_Read_Transmit('s');
        uart1_Read_Transmit('t');
        uart1_Read_Transmit('e');
        uart1_Read_Transmit('m');
        uart1_Read_Transmit(' ');
        uart1_Read_Transmit('O');
        uart1_Read_Transmit('p');
        uart1_Read_Transmit('e');
        uart1_Read_Transmit('r');
        uart1_Read_Transmit('a');
        uart1_Read_Transmit('t');
        uart1_Read_Transmit('i');
        uart1_Read_Transmit('o');
        uart1_Read_Transmit('n');
        uart1_Read_Transmit('\n');


        // uart1_Write_Transmit('L');
        // uart1_Write_Transmit('E');
        // uart1_Write_Transmit('D');
        // uart1_Write_Transmit(' ');
        // uart1_Write_Transmit('O');
        // uart1_Write_Transmit('f');
        // uart1_Write_Transmit('f');
        // uart1_Write_Transmit('\n');

        systemState = 0;
    }
    // else if (rxData == 'C')
    // {
    //     uart1_Write_Transmit('M');
    //     uart1_Write_Transmit('O');
    //     uart1_Write_Transmit('V');
    //     uart1_Write_Transmit('E');
    //     uart1_Write_Transmit('\n');
    // }
    else
    {

        uart1_Write_Transmit(rxData);
    }
}

void uart1Init()
{
    // 통신속도 9600bps 로 설정
    UBRR0H = 0;    // low
    UBRR0L = 0xcf; // hi 207

    // 2배속 mode setting
    UCSR0A |= (1 << U2X0);

    // 비동기, 8bit전송, 패리티없음, 1bit로 stop
    // UCSR0C에다 세팅해야되는데 기본값으로 다 지정되어있어서 안해도 됨

    //            수신         송신    세팅
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);

    // 수신 인터럽트 인에이블
    UCSR0B |= (1 << RXCIE0); // 기존의 polling방식에서 인터럽튼 방식으로 추가한 코드

    // 1번 설정
    UBRR1H = 0;    // low
    UBRR1L = 0xcf; // hi 207
    UCSR1A |= (1 << U2X1);
    UCSR1B |= (1 << RXEN1) | (1 << TXEN1);
    UCSR1B |= (1 << RXCIE1);
}

void uart1_Read_Transmit(char data)
{
    while (!(UCSR1A & (1 << UDRE1)))
        ; // 송신 가능 대기, UDR이 비어 있는가?

    // 비어 있다면 데이터 입력
    UDR1 = data;
}

void uart1_Write_Transmit(char data)
{
    while (!(UCSR0A & (1 << UDRE0)))
        ; // 송신 가능 대기, UDR이 비어 있는가?

    // 비어 있다면 데이터 입력
    UDR0 = data;
}

unsigned uart1Receive(void)
{
    while (!(UCSR0A & (1 << RXC0)))
        ; // 수신가능 대기

    // 데이터 출력
    return UDR0;
}

uint8_t uart1_System_Distance()
{
    uint8_t a = 2;

    a = systemState;
    systemState = 2;    //0 또는 1이 아닌 값을 넣어서 반복하는 현상 방지

    return a;
}