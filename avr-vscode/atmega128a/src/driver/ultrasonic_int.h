# include "common/def.h"

#define TRTGGER_DDR     DDRD
#define ECHO_DDR        DDRE    //d
#define TRIGGER_PORT    PORTD
#define ECHO_PORT       PINE    //D
#define TRIGGER_PIN     6
#define ECHO_PIN        7   //3

void ultrasonicInit();
void ultrasonicTrigger();
uint16_t ultrasonicDistance();
