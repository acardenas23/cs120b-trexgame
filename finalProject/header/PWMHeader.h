#ifndef PWMHEADER_H
#define PWMHEADER_H
void set_PWM(double frequency) {
	static double current_frequency;
	if(frequency != current_frequency){
		if(!frequency) {TCCR3B &= 0x08; }
		else {TCCR3B |= 0x03; }
		if(frequency < 0.945) {OCR3A = 0xFFFF; }
		else if (frequency > 31250) { OCR3A = 0x0000; }
		else { OCR3A = (short) (8000000 / (128 * frequency)) - 1; }
		TCNT3 = 0; //resets counter
		current_frequency = frequency;
	}
}
void PWM_on(){
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

#endif

//Phase and Frequency Correct Mode
//want 20ms
