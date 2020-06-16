/*
 * File:   main.c
 * Author: emad_
 *
 * Created on June 7, 2020, 9:24 PM
 */

#define F_CPU 16000000UL	
#include <xc.h>
#include <util/delay.h>	
#include <avr/interrupt.h>
#include <string.h>
#include "mUART.h"
#include "DIO_1.h"
#include "mSPI.h"
#include "DIO.h"

#define _led_1_on  1
#define _led_2_on  2
#define _led_1_off 3
#define _led_2_off 4
// HOW THE CODE WORKS :
// the user write on virtual terminal on proteus a string foe example " led 1 on."
// the string transfer from virtual terminal to the master controller using UART protocol
// IF condition checks the string sent by the user with predefined strings in the code
// if the condition is true a character is set with a value and sent to the slave using SPI protocol   
// 

int main(void) {
    char led1on;
    char led2on;
    char led1off;
    char led2off;
    char doubledot_led1on_char;
    char doubledot_led2on_char;
    // all charaters above used for taking the value returned from the compare string function

    char _spi = 0; // this variable is set differently and it depends on which condition is true

   

    char _led1on[20] = "led 1 on.";
    char doubledot_led1on[20] = "led 1 on..";
    char _led2on[20] = "led 2 on.";
    char doubledot_led2on[20] = "led 2 on..";
    char _led1off[20] = "led 1 off.";
    char _led2off[20] = "led 2 off.";
    UART_init(_Asynchronous, _disabled_Parity, _1_stop_bit, _8bit, 103); // initiates the the UART protocol
    SPI_MasterInit(_SPI_interrupt_OFF, _PS128, _DOUBLE_SPEED_OFF); // initiates the the SPI protocol
    char string1[40]; // the variable that the string sent by the user will be saved in it


    while (1) {
        SPI_MasterTransmit(_spi); // transmits the character to the slave using spi

        strcpy(string1, UART_ReceiveString()); // copies the string that sent by the user to the string called string1


        led1on = strcmp(_led1on, string1); // compares the predefined string and the string sent by the user and returns 0 if identical
        led2on = strcmp(_led2on, string1); // compares the predefined string and the string sent by the user and returns 0 if identical
        led1off = strcmp(_led1off, string1); // compares the predefined string and the string sent by the user and returns 0 if identical
        led2off = strcmp(_led2off, string1); // compares the predefined string and the string sent by the user and returns 0 if identical
        doubledot_led1on_char = strcmp(doubledot_led1on, string1); // compares the predefined string and the string sent by the user and returns 0 if identical
        doubledot_led2on_char = strcmp(doubledot_led2on, string1); // compares the predefined string and the string sent by the user and returns 0 if identical


        // IF condition that decide which led will be on or off 
        if (led1on == 0 || doubledot_led1on_char == 0) {
            _spi = _led_1_on; // the value is set so it can be sent using spi to the slave 
            *string1 = '\0'; // clear the string variable so it can new string from the user 

        } else if (led2on == 0 || doubledot_led2on_char == 0) {
            _spi = _led_2_on; // the value is set so it can be sent using spi to the slave
            *string1 = '\0'; // clear the string variable so it can new string from the user 
        } else if (led1off == 0) {
            _spi = _led_1_off; // the value is set so it can be sent using spi to the slave
            *string1 = '\0'; // clear the string variable so it can new string from the user 
        } else if (led2off == 0) {
            _spi = _led_2_off; // the value is set so it can be sent using spi to the slave
            *string1 = '\0'; // clear the string variable so it can new string from the user 

        }

    }
    return 0;
}

