/*	Author: acard079
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #11  Exercise #
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

	//using mode 14- fast PWM (page 177)
	//TCCR1A = Timer/Counter1 Control Register A
	TCCR1A |= 1 << WGM11 | 1 << COM1A1 | 1 << COM1A0; //shift operator to set bits, setting COM1A and COM10 to 1 sets inverting mode (pg176)
	TCCR1B |= 1 << WGM12 | 1 << WGM13 | 1 << CS10; //set WGM11,12,13 to 1 for mode 14; no prescaler
	//Servo motor needs 50Hz PWM
	ICR1 = 19999;//Default = 1MHz; 1MHz/50Hz = 20,000
	//period is 20ms-> 20,000/20 = 1000 => 1 ms is 1000
	//OCR1A is output pin for PWM (Output Compare Register 1A)
	//OCR1A = ICR1 - 1000; //will give 1ms ON in 20ms period=> 5% Duty Cycle

	ADC_init();

	while(1){
		x = ADC;
		//code to optain brightness level when there is cactus on screen (comment out)
		/*
		unsigned char lower8 = (char)x;
		
		PORTB = lower8;
		*/
		cactusval = 0x9A; //brightness level when there is cactus

		if(x <= cactusval){
			//there is cactus
			PORTB = 0x01;			
			OCR1A = ICR1 - 2000; //2ms period
			_delay_ms(100); //delay to ensure full rotation is made
		}else{
			//there is no cactus
			PORTB = 0x00;
			OCR1A = ICR1 - 1550; //position 0degrees ~1.5ms period
			_delay_ms(50);
		}
	}
	return 1;
}
