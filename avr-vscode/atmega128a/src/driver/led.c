#include "led.h"

void ledInit(LED *led)
{
    *(led->port - 1) |= (1 << led->pin); // 출력설정
}

void ledOn(LED *led)
{
    *(led->port) |= (1 << led->pin); // led 키기
}

void ledOff(LED *led)
{
    *(led->port) &= ~(1 << led->pin); // led 끄기(현제 led 반전)
}

void ledToggle(LED *led)
{
    *(led->port) ^= (1 << led->pin); // led 끄기(현제 led 반전)
}