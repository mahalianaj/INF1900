/*
*Names: Lysandra Kingne Welapenou (2276662), Mahaliana Jeansoulé (2267583), Sara Lynn Benkreira (2301399), Farah Sherif (2379205)
*
*Section: 03, team: 6275
*
*uart.h
*
*Description: This class manages communication between the memory and the PC via RS232, i.e., the exchange of messages in binary
* or ASCII characters. The class's initialization method defines the configuration of the ports through which the
* exchange takes place, as well as the frame speed and format. The transmission method manages the exchange and
* the content of the message itself.
*/

#ifndef H_UART
#define H_UART
#include <avr/io.h>


class Uart{

  public:
    Uart();
    void transmissionUART(uint8_t donnee);
    void transmitString(const char *donneeString);
    uint8_t receiveUART();
      
};


#endif