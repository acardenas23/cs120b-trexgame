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

unsigned short x = 0x000;
unsigned short cactusval = 0x00;
//Value of ADC register is now stored in variable x
//
void ADC_init(){
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRD = 0xFF; PORTD = 0x00;//Set PORTD to output since we are using OC1A Pin(PD5)
	TCCR1A |= 1 << WGM11 | 1 << COM1A1 | 1 << COM1A0; //shift operator to set bits, setting COM1A and COM10 to 1 sets inverting mode (pg176)
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS10;
	ICR1 = 19999;

	ADC_init();

	while(1){
		x = ADC;
	
		//code to optain brightness level when there is cactus on screen (comment out)
		/*
		unsigned char lower8 = (char)x;
		
		PORTB = lower8; //value obtained-> 0111 1111 = 0x7F
		*/
		cactusval = 0x9A; //brightness level when there is cactus

		if(x <= cactusval){
			//there is cactus
			PORTB = 0x01;
			
			OCR1A = ICR1 - 2000;
			_delay_ms(100); 
		}else{
			//there is no cactus
			PORTB = 0x00;
			OCR1A = ICR1 - 1550; //position 0
			_delay_ms(50);
		}

			
	}
	return 1;
}
