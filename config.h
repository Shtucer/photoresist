/*
 * config.h
 *
 *  Created on: 15 нояб. 2015 г.
 *      Author: Shtucer
 */

#ifndef CONFIG_H_
#define CONFIG_H_

// Buttons
#define	SW1 PB2
#define SW2	PB3
#define SW3	PB4
#define SW4	PB5

#define RELAY PB0

#define RelayOn() (PINB |= (1 << RELAY))
#define RelayOff() (PINB &= ~(1 << RELAY))

#define IsPressed(x) ((PINB) & _BV(x))

#endif /* CONFIG_H_ */
