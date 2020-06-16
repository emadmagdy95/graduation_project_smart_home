/*
 * File:   mUART.c
 * Author: emad_
 *
 * Created on May 27, 2020, 9:23 AM
 */


#include <xc.h>
#include "mUART.h"
#include <stdlib.h>


void UART_init(int mode, int parity_mode, int number_stop_bits, int data_size, unsigned int baud){
    /* Set baud rate */ 
    UBRRH = (unsigned char)(baud>>8);
    UBRRL = (unsigned char)baud;
    /* Enable receiver and transmitter */ 
    UCSRB = (1<<RXEN)|(1<<TXEN);
    /* Set frame format: 8data, 2stop bit */
    UCSRC = (mode<<URSEL)|(number_stop_bits<<USBS)|(data_size<<UCSZ0)|(parity_mode<<UPM0);

}
void UART_TransmitChar( unsigned char data ) {
    /* Wait for empty transmit buffer */ 
    while ( !( UCSRA & (1<<UDRE)) ) ;
    /* Put data into buffer, sends the data */ 
    UDR = data;
}

unsigned char UART_ReceiveChar( void ) {
    /* Wait for data to be received */ 
    while ( !(UCSRA & (1<<RXC)) ) ; 
    /* Get and return received data from buffer */ 
    return UDR;
}
 char* UART_ReceiveString( void ) {
  static   char string[20];
  static  char* temp;
    temp = string;
    
    while ((*temp=UART_ReceiveChar())!='.'){
        ++temp;
    }
    
    return string;
    
}
 int UART_ReceiveINT(void){
  int i;
  char c;
    for(int j=0; j<4; j++){
        c = UART_ReceiveChar();
        i=c;
       i = i<<8;
    }
    return i ;
 }
void UART_TransmitString( char *_data ){
    for(int i=0 ; _data[i] != '\0' ; i++){
        UART_TransmitChar(_data[i]);
    }
}

void UART_TransmitInt(int value){
    char buf[20];
    itoa(value,buf,10);  
    UART_TransmitString(buf);
}

void UART_TransmitNewLine(){
    char newline[] = "\t\r";
    UART_TransmitString(newline);
}
/*
 unsigned char *  _UART_ReceiveChar( void ) {
  
    static char data[10] ;
    while ( !(UCSRA & (1<<RXC)) );
  
    // Get and return received data from buffer 
    
     return UDR ;
    
}
*/
        