#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stc12.h>

__sfr __at(0x88) TCON;
__sfr __at(0x89) TMOD;
__sfr __at(0x8b) TL1;
__sfr __at(0x8d) TH1;
__sfr __at(0x8a) TL0;
__sfr __at(0x8c) TH0;

__sfr __at(0x98) SCON;
__sfr __at(0x99) SBUF;

__sfr __at(0xca) P5M0;
__sfr __at(0x80) P0; 		//8 bitPort0          P0.7  P0.6  P0.5  P0.4  P0.3  P0.2  P0.1  P0.0       1111,1111
__sfr __at(0x90) P1;		 //8 bitPort1          P1.7  P1.6  P1.5  P1.4  P1.3  P1.2  P1.1  P1.0       1111,1111
__sfr __at(0xA0) P2;		 //8 bitPort2          P2.7  P2.6  P2.5  P2.4  P2.3  P2.2  P2.1  P2.0       1111,1111
__sfr __at(0xb0) P3;
__sfr __at(0xC0) P4; 		//8 bitPort4          P4.7  P4.6  P4.5  P4.4  P4.3  P4.2  P4.1  P4.0       1111,1111
__sfr __at(0xC8) P5;		 //8 bitPort5           -     -       -      -    P5.3  P5.2  P5.1  P5.0    xxxx,1111

__sbit __at(0xB0) P30; // RXD
__sbit __at(0xB1) P31; // TXD

__sfr __at(0xa8) IE;

__sfr __at(0xba) P_SW2;

#define LED P1_0 // LED 

int putchar(int c)
{
	while(!(SCON & 0x02));
	SCON &= ~0x02;
	SBUF = c;
	return (c);
}
void set4800serial(void)
{
// Configure UART for Timer1 (mode 2 : SMOD = 0) ,serial clock divisor = 12 (timer1), 11.0592 MHz clock, 4800 baud, 8 data bits, 1 stop bit.
	TMOD = 0x20;
	SCON = 0x40;
	TH1 = 0xFA;
//	TH1 = 256 - 11.0592 * 1000 * 1000 / 12 / 32 / 9600 + 0.5;
	TCON |= 0x40;
	SCON |= 0x02;				// Tell putchar() the UART is ready to send.
}

void delay (int loop_cnt)
{
    int cnt, ocnt;
    for (ocnt = 0; ocnt < 482; ocnt++) {
        for (cnt = 0; cnt < loop_cnt; cnt++) {
        __asm__ ("nop");
        }
    }
}

void main(void)
{
	unsigned long int i = 0;
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Configure UART for Timer1 (mode 2 : SMOD = 0) ,serial clock divisor = 12 (timer1), 11.0592 MHz clock, 9600 baud, 8 data bits, 1 stop bit.
	TMOD = 0x20;
	SCON = 0x40;
	TH1 = 0xFD;
	TCON |= 0x40;
	SCON |= 0x02;				// Tell putchar() the UART is ready to send.
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	LED = 0;	P1 = 0;	P2 = 0;	P4 = 0;
	for(;;)
	{
	printf("STC12C5A60S2\n");	      printf("Baud 9600\n");
	LED = 1;        delay (500);           LED = 0;        delay (500);
	P1 = 1;        delay (500);             P1 = 0;        delay (500);
	P2 = 1;        delay (500);             P2 = 0;        delay (500);
	P4 = 1;        delay (500);             P4 = 0;        delay (500);
		// for(i = 0; i < 147456; i++); // Sleep
	}
}