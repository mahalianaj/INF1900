#ifndef DEBUG_H
#define DEBUG_H // à mettre en commentaire ou non au besoin


#include <avr/io.h>
#include "uart.h"

#ifdef DEBUG
Uart uart;
#define DEBUG_PRINT(x) uart.transmitString(x) // ou par RS-232
#else
#define DEBUG_PRINT(x) do {} while (0) // code mort
#endif
#endif
