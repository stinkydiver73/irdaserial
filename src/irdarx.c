/*
    IRDA serial RX
    
    19200 Baud

(C) 2021, Stinkydiver73
 */

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "common.h"

void irdarx_setup()
{
    cli();

    //TIMER0 setup
    PRR |= (0 << PRTIM0); //Enable Timer0 (default)
    TCCR0A = 0;           //Clear TCCR0A
    TCCR0B = 0;           //Clear TCCR0B
    TCCR0A |= (1 << WGM01) | (0 << WGM00);
    TCCR0B |= (0 << WGM02);                            //mode2 CTC
    TCCR0B |= (0 << CS02) | (1 << CS01) | (0 << CS00); //Set Timer0 prescaler to 8 (0.5us)
    OCR0A = (uint8_t)106;                                       // 52us (52.08>uS)
    //TIMSK0 = (1 << OCIE0A);// Output Compare Match A Interrupt Enable

    //PIN change interrupt setup PORTB1

    // Enable pin change interrupt on the PB1 (PCINT1) pin using Pin Change Mask Register 0 (PCMSK0)
    PCMSK0 |= (1 << PCINT1);

    // Enable pin change interrupt 0 using the Pin Change Interrrupt Control Register (PCICR)
    PCICR |= (1 << PCIE0);

    //sei();
}

ISR(TIMER0_COMPA_vect)
{
    SET_TXD_PIN();
    TIMSK0 = (0 << OCIE0A); // Output Compare Match A Interrupt Disable
}

//pin change PB1 (IRDA Rx)
ISR(PCINT0_vect)
{
    // Read PB1 using the Port D Pin Input Register (PINB)
    if (PINB & (1 << PINB1))
    {
        // PB1 is high (IR pulse)
        TCNT0=0x00;
        TIFR0=(1<<OCF0A);    //Clear Output Compare A Flag
        TIMSK0 = (1 << OCIE0A);// Output Compare Match A Interrupt Enable
        CLEAR_TXD_PIN();
    }
    else
    {
        // PB1 is low
    }
}
