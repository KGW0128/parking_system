#include "ap.h"

void apInit()
{
}

void apMain(void)
{
	uart0Init();

	extern FILE OUTPUT; // 어딘가에 선언된(uart0) OUTPUT 파일을 가져옴
	stdout = &OUTPUT;	// 주소값 전달
	sei();
	uint16_t distance = 0;
	ultraInit();

	while (1)
	{
		ultraTrigger();
		//_delay_ms(50);
		distance = ultraDistance();
		printf("distance : %d cm\r\n", distance);
		_delay_ms(500);
	}








	// uart0Init();

	// extern FILE OUTPUT; // 어딘가에 선언된(uart0) OUTPUT 파일을 가져옴
	// stdout = &OUTPUT;	// 주소값 전달

	// uint16_t distance = 0;
	// ultrasonicInit();
	// sei();

	// while (1)
	// {
	// 	ultrasonicTrigger();
	// 	//_delay_ms(50);	//인터럽트 발생 시간 확보
	// 	distance = ultrasonicDistance();
	// 	printf("distance : %d cm\r\n", distance);
	// 	_delay_ms(500);
	// }







	// uart0Init();

	// extern FILE OUTPUT;	//어딘가에 선언된(uart0) OUTPUT 파일을 가져옴
	// stdout = &OUTPUT;	//주소값 전달

	// extern volatile uint8_t rxFlag;
	// extern char rxBuff[100];

	// timerInit();
	// uint8_t distance;

	// while(1)
	// {
	// 	triggerPin();
	// 	distance = meanDistance();
	// 	printf("distance : %d cm\r\n",distance);
	// 	_delay_ms(500);
	// }







	// LCD_Init();
	// LCD_WriteStringXY(0,0,"Hello ATmega128a");

	// uint16_t count =0;
	// uint8_t buff[30];

	// while(1)
	// {
	// 	//오류가 뜰 수도 있는데 문제없이 그냥 빌드 됨
	// 	sprintf(buff,"count: %-5d",count++);
	// 	LCD_WriteStringXY(1,0,buff);
	// 	_delay_ms(500);
	// }
}