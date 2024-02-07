Hello  community,

I'm currently facing a peculiar issue with UART transmission on an 89C52 microcontroller using Keil C51 and simulating it in Proteus. The code snippet is provided below:

```
#include <reg52.h>
#include <intrins.h>
 
	// HERE:  When an array is declared then uart will send the first uart character twice,
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
	    //_nop_();		 // This makes no difference
    }
}
void main() {  
	UART_Init();			// Init uart
   // _nop_();				// This makes no difference
 	 UART_TxString("xyz"); // Send 3 chars
	 
    while(1) {
	 
    }
}
 
  
```


he issue I'm encountering is that when an array is declared (unsigned long myArrayDeclaration[4] = { 0x00FFF789, };), the UART transmission sends the first character twice, resulting in "xxyz" instead of the expected "xyz." If I remove the array declaration, the transmission works correctly.

I'm using a Keil C51 environment with the uVision 4 IDE and simulating the code in Proteus. The microcontroller is an 89C52 chip.

I appreciate any insights or suggestions on how to resolve this anomaly in UART transmission. Thank you in advance for your assistance.
