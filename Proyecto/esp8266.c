/*
 * esp8266.c
 *
 *  Created on: 3 jun. 2021
 *      Author: Juan Francisco
 */

#include <LPC407x_8x_177x_8x.h>
#include <stdio.h>
#include <string.h>
#include "esp8266.h"
#include "uart_lpc40xx.h"
#include "glcd.h"

uint8_t WIFI_connectWlan(char *ssid, char *pass){
	char buff[100];
	uint8_t res = 0;

	sprintf(buff, "AT+CWJAP=\"%s\",\"%s\"", ssid, pass);
	uart_transmitir_cadena(UART3, buff);
	uart_recibir_cadena(UART3, buff, 100);
	glcd_printf("\n%s", buff);
	uart_recibir_cadena(UART3, buff, 100);
	glcd_printf("\n%s", buff);
	uart_recibir_cadena(UART3, buff, 100);
	glcd_printf("\n%s", buff);
	

	return res;
}

uint8_t WIFI_sendJSON(char *host, uint16_t port, char *url, char *content){
	char buff[100];
	uint8_t hostLength = 0, urlLength = 0, contentLength = 0;
	uint8_t sendSize = 79;
	uint8_t i;

// ---------------------------------------------------------------------
	while(host[hostLength]){
		hostLength++;
	}

	while(url[urlLength]){
		urlLength++;
	}

	while(content[contentLength]){
		contentLength++;
	}

	sendSize += contentLength + hostLength + urlLength;
// ---------------------------------------------------------------------

	uart_transmitir_cadena(UART3, "AT+CIPMUX=0");
	uart_recibir_cadena(UART3, buff, 100);

	sprintf(buff, "AT+CIPSTART=\"TCP\",\"%s\",%d", host, port);
	uart_transmitir_cadena(UART3, buff);
	uart_recibir_cadena(UART3, buff, 100);

	sprintf(buff, "AT+CIPSEND=%d", sendSize);
	uart_transmitir_cadena(UART3, buff);
	uart_recibir_cadena(UART3, buff, 100);

	sprintf(buff, "POST %s HTTP/1.1", url);
	uart_transmitir_cadena(UART3, buff);
	sprintf(buff, "Host: %s", host);
	uart_transmitir_cadena(UART3, buff);
	uart_transmitir_cadena(UART3, "Content-Type: application/json");
	sprintf(buff, "Content-Length: %d", contentLength);
	uart_transmitir_cadena(UART3, buff);
	uart_transmitir_cadena(UART3, "");
	uart_transmitir_cadena(UART3, content);

	for(i = 0; i < 18; i++){
		uart_recibir_cadena(UART3, buff, 100);
	}
	return 0;
}

uint8_t WIFI_verifyResponse(char *str){
	uint8_t i = 0;
	if(str && str[0] && str[1] && str[2] && str[3] && str[4]){
		while(str[i + 2]){
			if(memcmp((str + i), "OK", 2) == 0){
				return 0x00;
			}
			i++;
		}

		i = 0;
		while(str[i + 5]){
			if(memcmp((str + i), "ERROR", 5) == 0){
				return 0x01;
			}
			i++;
		}
	}
	return 0x02;
}
