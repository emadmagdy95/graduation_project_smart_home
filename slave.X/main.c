/*
 * File:   main.c
 * Author: emad_
 *
 * Created on June 10, 2020, 9:25 PM
 */



#define F_CPU 16000000UL	
#include <xc.h>
#include <util/delay.h>	
#include <string.h>
#include "mSPI.h"
#include <avr/interrupt.h>
#include "DIO.h"

#define _led_1_on  1
#define _led_2_on  2
#define _led_1_off 3
#define _led_2_off 4

char _spi_recieve = 0; // vraiable to the save the character comes from the master
// HOW THE CODE WORKS:
// the master send the character using spi protocol to the slave 
// when the character is sent and the spi transmiting from the master is finished the spi interrupt flag set to 1 the interupt service routine will execute
// the interrupt service routine contains switch case 
//the leds will turn on off depends on the value of the character sent by the master 

ISR(SPI_STC_vect) {
    _spi_recieve = SPDR;

    switch (_spi_recieve) {
        case _led_1_on:
            setPIN(0, _portC); // setting the value of pin 0 in port c to be 1
            break;
        case _led_2_on:
            setPIN(1, _portC); // setting the value of pin 1 in port c to be 1
            break;
        case _led_1_off:
            resetPIN(0, _portC); // setting the value of pin 0 in port c to be 0
            break;
        case _led_2_off:
            resetPIN(1, _portC); // setting the value of pin 1 in port c to be 0
            break;
    }
}

int main(void) {
    SPI_SlaveInit(_SPI_interrupt_ON, _PS128, _DOUBLE_SPEED_OFF); // initializing  SPI protocol
    PORTCas(OUT); // set Port c direction as output
    sei(); // enable global interrupt
    while (1) {
    }
    return 0;
}
