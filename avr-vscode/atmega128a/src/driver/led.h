#include "common/def.h"
#define LED_DDR DDRB
#define LED_PORT PORTB

// 구저체 정의
typedef struct
{
    volatile uint8_t *port;
    uint8_t pin;

}LED;

void ledInit(LED *led);
void ledOn(LED *led);
void ledOff(LED *led);
void ledToggle(LED *led);
