/*
 * main.c
 *
 *  Created on: 8 may. 2021
 *      Author: Juan Francisco
 */

#define F_CPU 16000000UL
#define FOSC 16000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "lcd.h"
#include "usart.h"
#include "esp8266.h"

#define BUFF_SIZE 100
#define END_CHAR 0x00
#define LF_CHARACTER 0x0a
#define CR_CHARACTER 0x0d
#define NL_CHARACTER 0x15

volatile uint8_t buff[BUFF_SIZE];

ISR(USART_RX_vect){
	static uint8_t i = 0;
	cli();
	buff[i] = UDR;
	//LCDWriteStringXY(0, 0, (char*)buff);
	if(	(i == BUFF_SIZE)||
		((buff[i-1] == CR_CHARACTER)&&(buff[i] == LF_CHARACTER))||
		((buff[i-1] == LF_CHARACTER)&&(buff[i] == CR_CHARACTER))||
		((buff[i-1] == CR_CHARACTER)&&(buff[i] == NL_CHARACTER))||
		((buff[i-1] == NL_CHARACTER)&&(buff[i] == CR_CHARACTER))){
		buff[i-1] = 0x00;
		i = 0;
		//LCDClear();
		LCDWriteStringXY(0, 0, "                ");
		LCDWriteStringXY(0, 0, (char*)buff);
	}else{
		i++;
	}
	sei();
}

int main(){
	uint8_t count = 0;
	char str[4];

	USART_Init(MYUBRR);
	//sei();

	InitLCD(0);
	LCDClear();

	//WIFI_connectWlan("WLAN_J3A4", "20200430");
	//WIFI_connectWlan("WLAN_AA", "VsrRRJfv7kouQ");
	//WIFI_sendJSON("192.168.1.45", 8080, "/sensors", "{\"temp\":26.3}");
	WIFI_sendJSON("jfsr00.ddns.net", 5007, "/sensors", "{\"msg\":\"jaja xD\"}");

	while(1){
		itoa(count, str, 10);
		//USART_TransmitStr(str);
		//USART_TransmitStrCR_LF(str);
		LCDWriteStringXY(0, 1, "                ");
		LCDWriteStringXY(0, 1, str);
		count++;
		_delay_ms(1000);
	}
}

