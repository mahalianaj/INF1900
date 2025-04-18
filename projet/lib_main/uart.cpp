#define F_CPU 8000000UL
#include <avr/io.h>
#include "uart.h"

Uart::Uart()
{

    // 2400 bauds.
    UBRR0H = 0;
    UBRR0L = 0xCF;

    // reception and transmission by  UART0
    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    // Format des trames: 8 bits, 1 stop bits, sans parité
    // UCSR0C &= ~(1<<UPM01) | ~(1<<UPM00) | ~(1<<USBS0) | ~(1<<USBS0);
    UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

void Uart::transmissionUART(uint8_t donnee)
{
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1 << UDRE0)))
        ;
    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

void Uart::transmitString(const char *donneeString)
{
    uint8_t i = 0;
    while (donneeString[i] != '\0')
    {
        transmissionUART(donneeString[i]);
        i++;
    }
}

uint8_t Uart::receiveUART() {
    while (!(UCSR0A & (1 << RXC0)))
        ;   
    return UDR0;
}