#include "project_main.h"

void project_Main(void)
{

	// 버튼 설정
	Button btnToggle1;		 // 버튼 1 (시스템 제어)
	Button btnToggle2;		 // 버튼 2 (모터 제어)
	uint8_t systemState = 0; // toggle변수(시스템)
	uint8_t pwmState = 0;	 // toggle변수(모터)

	// 버튼(토글 2개)
	Button_Init(&btnToggle1, &BUTTON_DDR, &BUTTON_PIN, BUTTON_TOGGLE_1);
	Button_Init(&btnToggle2, &BUTTON_DDR, &BUTTON_PIN, BUTTON_TOGGLE_2);

	uart0Init();  // 초음파 값 출력(거리 pc출력)
	uart1Init();  // 블루투스(모바일 통신)
	pwm16Init();  // 서브모터
	LCD_Init();	  // LCD
	pwm8Init();	  // 모터(환풍기)
	rgb_init();	  // RGB LED
	buzzerInit(); // 부저
	ultrasonicInit(); // 초음파모듈

	// nfc 통신 준비
	spi_init();
	mfrc522_init();

	set_color(0, 255, 0); //LED초기 색깔 녹색으로 설정


	extern FILE OUTPUT; // 어딘가에 선언된(uart0) OUTPUT 파일을 가져옴
	stdout = &OUTPUT;	// 주소값 전달

	uint16_t distance = 0;	//초음파 반환 거리값 저장 변수

	uint16_t lcd_count = 0; //lcd에 출력할 차량 대수 변수
	uint8_t buff[30];		//lcd에 출력할 문자를 담을 배열

	uint8_t uart1SystemDis = 2; //블루투스에서 받은 시스템 신호를 담을 변수(1 또는 0이 아닌 수)


	//NFC관련 변수
	uint8_t nfc_byte;
	uint8_t str[MAX_LEN];

	//NFC 셋팅
	nfc_byte = mfrc522_read(VersionReg); //NFC상태 받아옴

	// //LFC 상태 확인 출력
	// if (nfc_byte == 0x92)
	// {
	// 	printf("v1 Detected");
	// }
	// else if (nfc_byte == 0x91 || nfc_byte == 0x90)
	// {
	// 	printf("v2 Detected");
	// }
	// else
	// {
	// 	printf("no Detected");
	// }

	nfc_byte = mfrc522_read(ComIEnReg);
	mfrc522_write(ComIEnReg, nfc_byte | 0x20);
	nfc_byte = mfrc522_read(DivIEnReg);
	mfrc522_write(DivIEnReg, nfc_byte | 0x80);
	nfc_byte = mfrc522_request(PICC_REQALL, str);

	uint8_t cardData = 3;	//NFC테그 확인 변수



	sei();	//인터럽트 사용

	while (1)
	{
		// nfc카드가 아직 안찍혔다면
		if ((nfc_byte == 3) && (cardData == 3))
		{
			//nfc 값 가져옴
			nfc_byte = mfrc522_request(PICC_REQALL, str);
			cardData = nfc_byte;	//변수에 받은 값 저장
			//printf("NFC DATA SET : %d\n", byte); //NFC받은 변수 출력
		}



		// 블루투스 통제 시스템 받아오기
		// 입력문자 누적되는 걸 방지하기 위한 분리조치
		uart1SystemDis = uart1_System_Distance();



		// 만약 nfc가 연결 되었디면(카드를 댔다면)
		if (cardData == 1)		// 관리자 시스템 작동
		{

			//블루투스로 받은 시스템 통제 저장
			if (uart1SystemDis == 1)
			{
				systemState = 1;
			}
			else if (uart1SystemDis == 0)
			{
				systemState = 0;
			}

			// 시스템 통제 버튼
			if (Button_getState(&btnToggle1) == ACT_RELEASE)
			{
				systemState = !systemState;
			}


			// 환풍기 통제 버튼
			if (Button_getState(&btnToggle2) == ACT_RELEASE)
			{
				pwmState = !pwmState;
			}


		}



		// 환풍기 구동 여부
		if (pwmState)
		{
			pwm8Run(250); // PWM 켜기
		}
		else
		{
			pwm8Run(0); // PWM 끄기
		}



		// 시스템 구동
		if (systemState)//시스템을 정지 시켰을 때
		{
			buzzerRun();	//경고소리 재생
			OCR3A = 135; 	// 문닫음

			//경고 문자 출력
			LCD_WriteStringXY(0, 0, "Warning!!!            ");
			LCD_WriteStringXY(1, 0, "                      ");

			set_color(255, 255, 0);	//LED 노란색으로 변경
		}
		else//시스템이 구동 하고 있을 때
		{
			buzzerStop();						//경고음 정지

			ultrasonicTrigger();				//초음파 트리거 작동
			distance = ultrasonicDistance();	//초음파 값 받아오기
			// printf("distance : %d cm\r\n", distance);	//초음파 거리 출력


			//차량이 있다고 인식 했을 때
			if (distance < 13)
			{
				set_color(255, 0, 0);						//LED 빨강으로 변경

				//LCD 화면 출력
				LCD_WriteStringXY(0, 0, "No Parking Space");//0번 화면
				lcd_count = 0; 								//주차 가능 대수 변수
				sprintf(buff, "Space : %-5d", lcd_count);	//1번 화면 출력값 대입
				LCD_WriteStringXY(1, 0, buff);				//1번화면

				OCR3A = 135;								//차량 진입 막기
				_delay_ms(30);								//서브 모터 구동을 위한 delay
			}
			else//주차 자리가 비어 있다면
			{
				set_color(0, 255, 0);						//LED 녹색으로 변경
				
				//LCD 화면 출력
				LCD_WriteStringXY(0, 0, "Welcome ^^            ");	//0번 화면
				lcd_count = 1;										//주차 가능 대수 변수
				sprintf(buff, "Space : %-5d", lcd_count);			//1번 화면 출력값 대입
				LCD_WriteStringXY(1, 0, buff);						//1번 화면

				OCR3A = 370;										//차량 진입 허가
				_delay_ms(30);										//서브 모터 구동을 위한 delay
			}
		}
	}
}
