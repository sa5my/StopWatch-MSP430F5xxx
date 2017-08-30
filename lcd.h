
#ifndef LCD_H_
#define LCD_H_

#include <msp430f5529.h>
#include <string.h>
#include <stdio.h>

// Delay Functions
#define delay_ms(x)		__delay_cycles((long) x* 1000)
#define delay_us(x)		__delay_cycles((long) x)

// Pins
#define EN		BIT4
#define RS		BIT6
#define DATA	0x0F

// Commands
#define CLEAR	0x01

// Functions
extern void lcdInitialize();									// Initialize LCD
extern void lcdEnable();							// Trigger Enable
extern void lcdData(unsigned char data);			// Send Data (Characters)
extern void lcdCommand(unsigned char cmd);			// Send Commands
extern void lcdClear();								// Clear LCD
extern void lcdStringWrite(char * text, int x, int y);		// Write string
extern void lcdIntWrite(int val, int x, int y);			// Write integer

#endif /* LCDLIB_H_ */
