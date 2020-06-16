/*
 * File:   mSPI.c
 * Author: emad_
 *
 * Created on May 28, 2020, 9:39 PM
 */


#include <xc.h>
#include "mSPI.h"

void SPI_MasterInit(char SPI_INTERRUPT_ENABLE , char _PRESCALER ,char _speed ) { 
    /* Set MOSI and SCK output, all others input */ 
    DDRB |= (1<<_MOSI)|(1<<_SCK) | (1<<_SS); 
    /* Enable SPI, Master, set clock rate fck/16 */ 
    SPCR |= (1<<SPE)|(1<<MSTR)|(SPI_INTERRUPT_ENABLE<<SPIE)|(_PRESCALER<<0); 
    SPSR |=(_speed<<SPI2X);
}

void SPI_SlaveInit(char SPI_INTERRUPT_ENABLE , char _PRESCALER ,char _speed) { 
    /* Set MISO output, all others input */ 
    DDRB |= (1<<_MISO); 
    /* Enable SPI */ 
    SPCR |= (1<<SPE)|(SPI_INTERRUPT_ENABLE<<SPIE)|(_PRESCALER<<0); 
     SPSR |=(_speed<<SPI2X);
}



void SPI_MasterTransmit(char cData){
    /* Start transmission */ 
    SPDR = cData; 
    /* Wait for transmission complete */ 
    while(!(SPSR & (1<<SPIF))) ;
}





char SPI_SlaveReceive(unsigned char data){
    /* Wait for reception complete */ 
    while(!(SPSR & (1<<SPIF))) ; 
    /* Return data register */ 
    data =  SPDR ;
    return data;
}

