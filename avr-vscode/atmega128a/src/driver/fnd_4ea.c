#include "fnd_4ea.h"


#define FND_DATA_DDR    DDRC    // 데이터 방향 설정
#define FND_SELECT_DDR    DDRG    // 디지트 방향 설정
#define FND_DATA_PORT    PORTC    // 데이터 출력
#define FND_SELECT_PORT    PORTG    // 디지트 출력







void FND_Init(void)
{
    FND_DATA_DDR = 0xFF;    // 데이터 핀을 출력으로 설정
    FND_SELECT_DDR = 0xFF;    // 디지트 핀을 출력으로 설정
    FND_SELECT_PORT = 0x00;    // 디지트 출력 0V로 시작
}

void FND_Display(uint16_t data)
{
    static uint8_t position = 0;    // 디지트 선택 변수
    uint8_t fndData[] =
    {
        0x3F,   //0 
        0x06,   //1
        0x5B,   //2
        0x4F,   //3
        0x66,   //4
        0x6D,   //5
        0x7D,   //6
        0x27,   //7
        0x7F,   //8
        0x67    //9
    };

    // DP를 켜기 위한 마스크
    uint8_t dpMask = 0x80;  // DP는 8번째 비트에 해당


    switch (position)
    {
        case 0:
            // 첫 번째 자리수 표시 (천의 자리)
            FND_SELECT_PORT &= ~(1<<0);  // 1번핀 LOW
            FND_SELECT_PORT |= (1<<1) | (1<<2) | (1<<3);  // 2, 3, 4번핀 HIGH
            FND_DATA_PORT = fndData[data / 1000];  // 천의 자리 데이터
            break;

        case 1:
            // 두 번째 자리수 표시 (백의 자리)
            FND_SELECT_PORT &= ~(1<<1);  // 2번핀 LOW
            FND_SELECT_PORT |= (1<<0) | (1<<2) | (1<<3);  // 1, 3, 4번핀 HIGH
            FND_DATA_PORT = fndData[data / 100 % 10] | dpMask;  // 백의 자리 데이터 + 점
            break;

        case 2:
            // 세 번째 자리수 표시 (십의 자리)
            FND_SELECT_PORT &= ~(1<<2);  // 3번핀 LOW
            FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<3);  // 1, 2, 4번핀 HIGH
            FND_DATA_PORT = fndData[data / 10 % 10]; // 십의 자리 데이터 
            break;

        case 3:
            // 네 번째 자리수 표시 (일의 자리)
            FND_SELECT_PORT &= ~(1<<3);  // 4번핀 LOW
            FND_SELECT_PORT |= (1<<0) | (1<<1) | (1<<2);  // 1, 2, 3번핀 HIGH
            FND_DATA_PORT = fndData[data % 10];  // 일의 자리 데이터
            break;
    }

    position++;    // 다음 자리로 이동
    position = position % 4;    // 4자리수로 순환
}



