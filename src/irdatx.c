/*
    IRDA serial TX
    
    19200 Baud

(C) 2021, Stinkydiver73
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include "common.h"

void irdatx_setup()
{
    //TIMER1 setup
    cli();
    PRR |= (0 << PRTIM1); //Enable Timer1 (default)
    TCCR1A = 0;           //Clear TCCR1A
    TCCR1B = 0;           //Clear TCCR1B

    TCNT1 = 0x0000;
    ICR1 = 0x0000; //set TOP to 0, counter will stuck here

    TCCR1A |= (1 << COM1B1) | (1 << COM1B0);           //OC1B set on match, clear at bottom
    TCCR1A |= (1 << WGM11) | (0 << WGM10);             //
    TCCR1B |= (1 << WGM13) | (1 << WGM12);             //mode14, fast PWM
    OCR1B = 0xffff - 6;                                //pulse lenght 3us
    TIMSK1 = (1 << TOIE1);                             //Overflow Interrupt Enable
    TCCR1B |= (0 << CS12) | (1 << CS11) | (0 << CS10); //Set Timer1 prescaler to 8 (0.5us)

    // Enable pin change interrupt on the PD0 (PCINT16) pin using Pin Change Mask Register 2 (PCMSK2)
    PCMSK2 |= (1 << PCINT16);

    // Enable pin change interrupt 2 using the Pin Change Interrrupt Control Register (PCICR)
    PCICR |= (1 << PCIE2);

    //sei();
}

//pin change PD0 (RxD)
ISR(PCINT2_vect)
{
    //DEBUG_TOOGLE();

    // Read PD0 using the Port D Pin Input Register (PIND)
    if (PIND & (1 << PIND0))
    {
        // RxD is high (PD0)
        TCCR1A &= ~(1 << COM1B1) | (1 << COM1B0); //OC1B disconnect
    }
    else
    {
        //DEBUG_TOOGLE();

        // RxD is low (PD0)
        //start TIMER1
        TCNT1 = (0xFFFF - 52); //pulse start delay ~26us
        TCCR1A |= (1 << COM1B1) | (1 << COM1B0); //OC1B set on match, clear at bottom
    }
}

ISR(TIMER1_OVF_vect)
{
//    DEBUG_TOOGLE();
    TCNT1 = (0xFFFF - 95); //next pulse delay 47us (<52us)
}