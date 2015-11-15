/*
 * main.c
 *
 *  Created on: 27 окт. 2015 г.
 *      Author: Shtucer
 */
#define F_CPU	12000000UL

#include <avr/io.h>

#include <util/delay.h>
#include <avr/interrupt.h>


// Buttons
#define	SW1 PB2
#define SW2	PB3
#define SW3	PB4
#define SW4	PB5

#define IsPressed(x) ((PINB) & _BV(x))

#define RELAY PB0

#define RelayOn() (PINB |= (1 << RELAY))
#define RelayOff() (PINB &= ~(1 << RELAY))



void display(int);
// dp G F D E C B A
unsigned char DIGITS[]={
		0b11000000	// 0
		,0b11111001	// 1
		,0b10100100	// 2
		,0b10101000	// 3
		,0b10011001	// 4
		,0b10001010	// 5
		,0b10000010	// 6
		,0b11111000	// 7
		,0b10000000	// 8
		,0b10001000	// 9
};

unsigned char SYMBOLS[]={
		 0b10111111 // -

};
// Video memory
unsigned char data[4] = {0,0,0,0};

volatile unsigned char count=0;

int clkcounter=0;
volatile int i = 1234;

// Update display
ISR(TIMER0_OVF_vect){
#ifdef DEBUG
	static char totalOVF=0;
	if(totalOVF>=0){
#endif
	PORTC = ~_BV(count);

	PORTD = data[count];
	count = (count+1)%4;
#ifdef DEBUG
	totalOVF=0;
	}
	totalOVF++;
#endif

}



// Check the Buttons
ISR(TIMER2_OVF_vect){

	if(IsPressed(SW1)){
		PORTC |= _BV(PC4);
	}
	else {
		PORTC &= ~_BV(PC4);
	}

	//PORTC ^= _BV(PC4);
}



void setup_io(){
	ACSR |= (1 << ACD);

	// Cathodes pins to output mode
	DDRC |= 1 << PC0; // CTA4
	DDRC |= 1 << PC1; // CTA3
	DDRC |= 1 << PC2; // CTA2
	DDRC |= 1 << PC3; // CTA1

	// Cathodes pins to HIGH (0 - ON, 1 - OFF)
	PORTC |= (1 << PC0);
	PORTC |= (1 << PC1);
	PORTC |= (1 << PC2);
	PORTC |= (1 << PC3);

	DDRC |= 1 << PC5;
	DDRC |= 1 << PC4;
	PORTC |= (0 << PC5) | (0 << PC4);

	DDRB |= (1 << RELAY);
	PORTB &= ~(1 << RELAY);
	RelayOn();

	DDRB |= 0 << SW1;
	DDRB |= 0 << SW2;
	DDRB |= 0 << SW3;
	DDRB |= 0 << SW4;

	// Buttons pullup
	PORTB &= ~(1 << SW1); // SW1
	PORTB &= ~(1 << SW2); // SW2
	PORTB &= ~(1 << SW3); // SW3
	PORTB &= ~(1 << SW4); // SW4

	// Anodes (segments) pins to output
	DDRD |= 1 << PD0; // A
	DDRD |= 1 << PD1; // B
	DDRD |= 1 << PD2; // C
	DDRD |= 1 << PD3; // E
	DDRD |= 1 << PD4; // D
	DDRD |= 1 << PD5; // F
	DDRD |= 1 << PD6; // G
	DDRD |= 1 << PD7; // dp

	// Anodes (segments) pins to HIGH  (0 - ON, 1 - OFF)
	PORTD = 0xff; //0b11111111; // OFF all segments


#ifdef DEBUG
	TCNT0 = 220;
#else
	TCNT0 = 0;
#endif

	// Timer0 - display update
	// /8 prescaler
	TCCR0 |=  (0 << CS02) | (1 << CS01) | (0 << CS00);
	// start timer0
	//TIMSK |= (1 << TOIE0);

	// Timer1 - time counter (every 1sec)


//	TCCR1B |= (0 << CS02) | (1 << CS01) | (1 << CS00);
//	TCNT1 = 0x02;

	// Timer2 - button events
	// every 1ms
	// /8 prescaler
	ASSR |= (0 << AS2); // Connect timer to TOSC1
	TCCR2 |=  (0 << CS22) | (1 << CS21) | (1 << CS20);
	TCNT2 = 47;
	TIMSK |= (1 << TOIE2);
}
/*
void _display_digit(int pos, int dig){


	PORTC = _BV(POS[pos]);
//	PORTD = 0x00;
//	PORTC |= ((1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3));

	PORTD = dig;

	//_delay_ms(10);
	//PORTC |= (1 << POS[pos]);
	//PORTC |= (1 << POS[pos]);
}

void display(int integer){
		_display_digit(0, data[0]);
		_display_digit(1, data[1]);
		_display_digit(2, data[2]);
		_display_digit(3, data[3]);

}
*/

int main(void){
//	cli();
	setup_io();

	sei();


	//short pos = 0;
	while(1){
		data[0] = DIGITS[i % 10];
		data[1] = DIGITS[(i/10)%10];
		data[2] = DIGITS[(i/100)%10];
		data[3] = DIGITS[(i/1000)];
		//_display_digit(count, data[count]);

//		display(0);
//		PORTC |= ((1<<PC0) | (1<<PC1) | (1<<PC2) | (1<<PC3));
//		PORTC &= ~(1 << POS[0]);
//		_delay_ms(10);
		//i++;
		//PORTB ^= _BV(PB5);
	}
	return 0;
}

