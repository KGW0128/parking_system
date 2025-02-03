#include "common/def.h"

//포트 및 핀 선언
#define LED_DDR		DDRB
#define LED_PORT	PORTB
#define BUTTON_DDR	DDRC	//D
#define BUTTON_PIN	PINC	//D

//버튼 1, 2, 3번
#define BUTTON_ON		0
#define BUTTON_OFF		1
#define BUTTON_TOGGLE	2


#define BUTTON_TOGGLE_1   6     // 차단기
#define BUTTON_TOGGLE_2   7     // 환풍기



enum{
	PUSHED,	//눌림
	RELEASED//안눌림
};

enum{
	NO_ACT,		//아무것도 안함
	ACT_PUSH,	//눌린상태
	ACT_RELEASE,	//안눌린상태
	ACT_TOGGLE	//토글
};

typedef struct
{
    volatile uint8_t *ddr;
    volatile uint8_t *pin;
   
   
    uint8_t btnPin;
    uint8_t prevState;
	uint8_t toggleState; // 토글 상태
}Button;


void Button_Init(Button *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum);
uint8_t Button_getState(Button *button);
