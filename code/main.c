#include <reg52.h>
#include <intrins.h>
 
	// When an array is declared then uart will send the first uart character twice,
 	unsigned long myArrayDeclaration[4] = { 	0x00FFF789,  };
	// If the line above exists , UART will wrongly send "xxyz", instead of "xyz", nonsense. 

 
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
			 //_nop_();				 // This makes no difference
    }
}
void main() { 
	
	UART_Init();					 // Init uart
   // _nop_();					 // This makes no difference
 	 UART_TxString("xyz"); // Send 3 chars
	 
    while(1) {
	 
    }
}
 
  