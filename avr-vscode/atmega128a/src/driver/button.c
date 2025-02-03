#include "button.h"


void Button_Init(Button *button, volatile uint8_t *ddr, volatile uint8_t *pin, uint8_t pinNum)
{
	button->ddr = ddr;  //버튼 ddr 설정
	button->pin = pin;  //버튼 핀 설정
		button->btnPin = pinNum;//핀 번호 부여(버튼 0, 1, 2)
	button->prevState = RELEASED;		//초기값을 1로 설정(아무것도 안누른 상태로 시작)
	*button->ddr &= ~(1<<button->btnPin); //버튼 핀을 입력으로 설정(그 주소가 가리키는 값)
}




uint8_t Button_getState(Button *button)
{

    //버튼의 현재 상태를 읽어옴
	uint8_t curState = *button->pin & (1<<button->btnPin);
	
	
	//눌렀다면				//넘겨 받은 버튼의 상태(안눌린 상태에서)
	if((curState==PUSHED)&& ((button->prevState)==RELEASED))//안누른 상태에서 누르면
	{
		_delay_ms(50);				//디바운스 코드
		button->prevState = PUSHED; //누름으로 변경
		return ACT_PUSH;			//누름으로 반환
	}
	
	//버튼을 띄었다면				//눌린상태에서
	else if((curState != PUSHED)&& ((button->prevState)==PUSHED))//버튼을 누른상태에서 때면
	{
		_delay_ms(50);					//디바운스 코드
		button->prevState = RELEASED;	//안누름으로 변경
		return ACT_RELEASE;				//안누름 반환
	}

    // 버튼이 눌린 상태에서 계속 눌려 있을 때 (토글을 위한 조건)
    else if ((curState == PUSHED) && (button->prevState == PUSHED))
    {
        //_delay_ms(50);                // 디바운싱
        button->prevState = RELEASED; // 상태 반전
        return ACT_TOGGLE;            // 토글 동작
    }



	
	
	return NO_ACT;	//아무것도 안했다는걸 반환


}