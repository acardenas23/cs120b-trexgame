/*	Author: acard079
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#define F_CPU 1000000
#include <util/delay.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	DDRD = 0xFF; PORTD = 0x00; //set PORTD to output since we are using OC1A Pin(PD5)
	TCCR1A |= 1<<WGM11 | 1<< COM1A1 | 1<< COM1A0; //shift operator to set bits, setting COM1A1 and COM1A0 to 1 sets inverting mode(pg 176)
	TCCR1B |= 1<< WGM12 | 1<<WGM13 | 1 << CS10; 
	ICR1 = 19999;

	//OCR1A = ICR1 - 1500; //~18,000
	//Default 1MHz want 50Hz -> 1MHz/50Hz = 20,000 in 20ms period
	//20,000/20ms = 1,000 -> 2ms = 2,000
   while (1) {
	   OCR1A = ICR1 - 1550;
	   _delay_ms(500);
	   OCR1A = ICR1 - 2000;
	   _delay_ms(500);


    }
    return 1;
}
