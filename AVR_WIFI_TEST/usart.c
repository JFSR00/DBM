/*
 * usart.c
 *
 * Created: 12/04/2021 11:51:52
 *  Author: DCE
 */ 

#include "usart.h"

void USART_Init(uint16_t ubrr){
	//1.-Set baud rate
	UBRRH = (uint8_t) (ubrr>>8);
	UBRRL = (uint8_t) ubrr;
	//2.-Set the speed: Normal Asynchronous
	UCSRA &= ~(1<<U2X);
	//UCSRA |= (1<<U2X);	// Activa la velocidad doble
	//3.-Enable receiver and transmitter
	UCSRB |= (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	//4.-Set frame format: 8data, 1stop bit
	UCSRC = 0b10000110;
}

void USART_Transmit_Char(uint8_t data ){
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) );
	/* Put data into buffer, sends the data */
	UDR = data;
}

void USART_Transmit(uint8_t *data, uint16_t size){
	while(size){
		USART_Transmit_Char(*data);
		data++;
		size--;
	}
}

void USART_TransmitStr(char *str){
	while(*str){
		USART_Transmit_Char((uint8_t)*str);
		str++;
	}
}

void USART_TransmitStrCR_LF(char *str){
	USART_TransmitStr(str);
	USART_SendCR_LF();
}

void USART_SendCR_LF(){
	USART_Transmit_Char(0x0d);
	USART_Transmit_Char(0x0a);
}

uint8_t USART_Receive_Char(){
	/* Wait for data to be received */
	while ( !(UCSRA & (1<<RXC)) );
	/* Get and return received data from buffer */
	return UDR;
}

void USART_Receive_UpTo(uint8_t *buff, uint16_t buff_size, uint8_t end){
	if(buff_size && buff){		// Comprobamos que el buffer no es un puntero nulo y que su tama�o es distinto de 0
								// We verify that the buffer isn't NULL pointer and it's size is distinct of 0
		do{
			*buff = USART_Receive_Char();
			buff++;
			buff_size--;
		} while (buff_size && (*(buff - 1) != end));
	}
}

void USART_Receive_UpTo_CR_LF(char *buff, uint16_t buff_size){
	if(buff_size && buff){		// We verify that the buffer isn't NULL pointer and it's size is distinct of 0
		do{
			*buff = USART_Receive_Char();
			buff++;
			buff_size--;
		} while (buff_size &&
				((*(buff - 2) != CR_CHARACTER)||(*(buff - 1) != LF_CHARACTER))&&
				((*(buff - 2) != LF_CHARACTER)||(*(buff - 1) != CR_CHARACTER))&&
				((*(buff - 2) != CR_CHARACTER)||(*(buff - 1) != NL_CHARACTER))&&
				((*(buff - 2) != NL_CHARACTER)||(*(buff - 1) != CR_CHARACTER)));
	}
}
