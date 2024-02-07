#ifndef UART_H
#define UART_H

#include <reg52.h>

void UART_Init(void) ;  
void UART_TxString(const char *string);
void UART_TxBytes(const unsigned char *bytes, unsigned int length);
void UART_Listen();
#endif
