/*
    IRDA - serial adapter
    
    19200 Baud IRDA

    IRDA input:  PB1 (PCINT1) , arduino nano D9
    IRDA output: PB2, arduino nano D10
    RxD:    PD0 (PCINT16) D0
    TxD:    PD1           D1

    Debug pin:  PD2, arduino nano D2
    LED         PB5

(C) 2021, Stinkydiver73
 */

#include <stdlib.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include "common.h"

void irdarx_setup();
void irdatx_setup();

int main(void)
{

    DDRB = (1 << PB5);  //LED output
    DDRD |= (1 << PD2); //debug output

    DDRB |= (1 << PB2);  //PORTB2 IRDA TX output (OC1B)
    DDRB |= (0 << PB1);  //PORTB1 IRDA RX input (PCINT1)
    PORTB |= (1 << PB1); //PORTB1 IRDA RX pin pullup

    DDRD |= (1 << PD1);  //PORTD1 TxD output (sw)
    DDRD |= (0 << PD0);  //PORTD0 RxD input (PCINT16)
    PORTD |= (1 << PD0); //PORTD0 RxD pin pullup

    _delay_ms(200);
    LED_ON();
    DEBUG_SET();
    _delay_ms(300);
    DEBUG_CLEAR();
    LED_OFF();

    irdarx_setup();
    irdatx_setup();

    sei();

    for (;;)
    {
        //_delay_ms(1);
    } //infinite loop
} //main
