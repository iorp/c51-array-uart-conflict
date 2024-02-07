
#include "uart.h"


sbit UART_RXD = P3^0;  // RXD pin
sbit UART_TXD = P3^1;  // TXD pin

void UART_Init() { 
    TMOD |= 0x20;    // Timer 1, Mode 2 (8-bit auto-reload)  
    // TH1 = 0xFD;      // Set baud rate for 9600 bps at 11.0592 MHz crystal
    TH1 = 0xFA;       // Set baud rate for 9600 bps at 22.1184 MHz crystal
    TL1 = TH1;
 
    TR1 = 1;         // Start Timer 1

    SCON = 0x50;     // Set serial mode 1 (8-bit UART)
    EA = 1;          // Enable global interrupts
    ES = 1;          // Enable serial interrupt
}



void UART_TxString(const char *string) {
    while (*string != '\0') {
        SBUF = *string;  // Send character
        while (!TI);     // Wait for transmit complete
        TI = 0;          // Clear transmit interrupt flag
        string++;        // Move to the next character
			 
    }
}

void UART_TxBytes(const unsigned char *bytes, unsigned int length) {
    unsigned int i =0;
    for (i = 0; i < length; i++) {
        SBUF = bytes[i];  // Send byte
        while (!TI);      // Wait for transmit complete
        TI = 0;           // Clear transmit interrupt flag
    }
}

void UART_Listen() {
    unsigned char receivedData;

    // COMMAND LOGIC GOES HERE 

    if (RI) {
        receivedData = SBUF;  // Read the received character
        RI = 0;               // Clear the receive interrupt flag

        // Process the received data (mirror it back)
        SBUF = receivedData;  // Send the character back
        while (!TI);          // Wait for the transmit to complete
        TI = 0;               // Clear the transmit interrupt flag
    }
}

 
