#pragma once

#define LED_ON() (PORTB |= (1 << PB5))
#define LED_OFF() (PORTB &= ~(1 << PB5))
#define LED_TOOGLE() (PORTB ^= (1 << PB5))

#define SET_TXD_PIN() (PORTD |= (1 << PD1))
#define CLEAR_TXD_PIN() (PORTD &= ~(1 << PD1))
#define TOOGLE_TXD_PIN() (PORTD ^= (1 << PD1))

#define DEBUG_SET() (PORTD |= (1 << PD2))
#define DEBUG_CLEAR() (PORTD &= ~(1 << PD2))
#define DEBUG_TOOGLE() (PORTD ^= (1 << PD2))
