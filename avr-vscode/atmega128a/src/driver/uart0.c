#include "uart0.h"


// 출력 스트림 설정 <stdio.h> 에 있는 표준 입출력임
FILE OUTPUT = FDEV_SETUP_STREAM(uart0Transmit, NULL, _FDEV_SETUP_WRITE); //uart0Transmit를 할껀데 null까지 써서 OUTPUT에 넣음





char rxBuff[100] = {0}; //수신버퍼
volatile uint8_t rxFlag = 0;


ISR(USART0_RX_vect)//수신 인터럽트 핸들러
{
    static uint8_t rxHead = 0; //수신된 데이터의 인덱스
    uint8_t rxData  = UDR0;



    if(rxFlag == 1)
    {
        //수신 플래그가 셋되어 있다면 아무것도 안하고
        //받은문자 버림
        return;
    }
    else if(rxData == '\n' || rxData == '\r') //계행이나 리턴문자이면
    {
        rxBuff[rxHead] = '\0';  //수신된 문자열 마지막에 NULL문자 추가
        rxHead = 0;             //인덱스 초기화
        rxFlag = 1;             //문자 받았다고 깃발 세움
    }
    else//그렇지 않다면
    { 
        rxBuff[rxHead] = rxData; //버퍼에 계속 데이터 추가
        rxHead++;                //인덱스 증가       
    }

}




void uart0Init()
{
    //통신속도 9600bps 로 설정
    UBRR0H = 0;     //low
    UBRR0L =0xcf;    //hi 207

    //2배속 mode setting
    UCSR0A |= (1<<U2X0);

    //비동기, 8bit전송, 패리티없음, 1bit로 stop
    //UCSR0C에다 세팅해야되는데 기본값으로 다 지정되어있어서 안해도 됨

    //            수신         송신    세팅
    UCSR0B |= (1<<RXEN0) | (1<<TXEN0);

    
    // 수신 인터럽트 인에이블
    UCSR0B |=(1<<RXCIE0);//기존의 polling방식에서 인터럽튼 방식으로 추가한 코드
}


void uart0Transmit(char data)
{
    while (!(UCSR0A & (1<<UDRE0))); //송신 가능 대기, UDR이 비어 있는가?

    //비어 있다면 데이터 입력
    UDR0 = data;
}


unsigned uart0Receive(void)
{
    while (!(UCSR0A & (1<<RXC0)));//수신가능 대기

    //데이터 출력
    return UDR0;
}


