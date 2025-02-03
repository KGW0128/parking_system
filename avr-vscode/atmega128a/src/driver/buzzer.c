#include "buzzer.h"



void buzzerInit(void)
{
    DDRA = 0xff;  
}



void buzzerRun()
{   
   
    PORTA = 0xff;
}


void buzzerStop()
{
    PORTA = 0x00;
}