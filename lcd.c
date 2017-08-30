#include "lcd.h"

#define	LOWNIB(x)	P3OUT = (P3OUT & 0xF0) + (x & 0x0F)

void lcdInitialize() 
{
	delay_ms(100);
	// Wait for 100ms after power is applied.

	P3DIR = EN + RS + DATA;  // Make pins outputs
	P3OUT = 0x03;  // Start LCD (send 0x03)

	lcdEnable(); // Send 0x03 3 times at 5ms then 100 us
	delay_ms(5);
	lcdEnable();
	delay_ms(5);
	lcdEnable();
	delay_ms(5);

	P3OUT = 0x02; // Switch to 4-bit mode
	lcdEnable();
	delay_ms(5);


	lcdCommand(0x33);
	lcdCommand(0x32);
	lcdCommand(0x28); // 4-bit, 2 line, 5x8
	lcdCommand(0x08); // Instruction Flow
	lcdCommand(0x01); // Clear LCD
	lcdCommand(0x06); // Auto-Increment
	lcdCommand(0x0C); // Display On, No blink
}

void lcdEnable() 
{
	P3OUT |= EN;
	delay_ms(2);
	P3OUT &= ~EN;
}

void lcdData(unsigned char data) 
{
	P3OUT |= RS; // Set RS to Data
	LOWNIB(data >> 4); // Upper nibble
	lcdEnable();
	LOWNIB(data); // Lower nibble
	lcdEnable();
	delay_us(50); // Delay > 47 us
}

void lcdCommand(unsigned char cmd)
{
	P3OUT &= ~RS; // Set RS to Data
	LOWNIB(cmd >> 4); // Upper nibble
	lcdEnable();
	LOWNIB(cmd); // Lower nibble
	lcdEnable();
	delay_ms(5); // Delay > 1.5ms
}

void lcdStringWrite(char* text, int x, int y)
{
	int i;
	if (x < 16) {
		x |= 0x80; // Set LCD for first line write
		switch (y){
		case 1:
			x |= 0x40; // Set LCD for second line write
			break;
		case 2:
			x |= 0x60; // Set LCD for first line write reverse
			break;
		case 3:
			x |= 0x20; // Set LCD for second line write reverse
			break;
		}
		lcdCommand(x);
	}
	i = 0;

	while (text[i] != '\0') {
		lcdData(text[i]);
		i++;
	}
}

void lcdIntWrite(int val, int x, int y)
{
	char number_string[16];
	sprintf(number_string, "%d", val); // Convert the integer to character string
	lcdStringWrite(number_string, x, y);
}

void lcdClear() 
{
	lcdCommand(CLEAR);
}
