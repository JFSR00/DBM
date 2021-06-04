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
	uint8_t res = WIFI_OK;

	sprintf(buff, "AT+CWJAP=\"%s\",\"%s\"", ssid, pass);
	uart_transmitir_cadena(UART3, buff);
	uart_recibir_cadena(UART3, buff, 100);
	res = WIFI_verifyResponse(buff);
	if(res != WIFI_OTHER){return res;}
		
	glcd_printf("\n%s", buff);
	uart_recibir_cadena(UART3, buff, 100);
	res = WIFI_verifyResponse(buff);
	if(res != WIFI_OTHER){return res;}
	
	glcd_printf("\n%s", buff);
	uart_recibir_cadena(UART3, buff, 100);
	res = WIFI_verifyResponse(buff);
	if(res != WIFI_OTHER){return res;}
	
	glcd_printf("\n%s", buff);
	

	return res;
}

uint8_t WIFI_sendJSON(char *host, uint16_t port, char *url, char *content){
	char buff[100];
	uint8_t hostLength = 0, urlLength = 0, contentLength = 0;
	uint8_t sendSize = 79;
	uint8_t i;
	
	uint8_t res = WIFI_OK;

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
	//res = WIFI_verifyResponse(buff);
	//if(res != WIFI_OK){return res;}
	
	glcd_printf("\n%s", buff);

	sprintf(buff, "AT+CIPSTART=\"TCP\",\"%s\",%d", host, port);
	uart_transmitir_cadena(UART3, buff);
	uart_recibir_cadena(UART3, buff, 100);
	res = WIFI_verifyResponse(buff);
	if(res == WIFI_ERROR){return res;}
	
	glcd_printf("\n%s", buff);

	sprintf(buff, "AT+CIPSEND=%d", sendSize);
	uart_transmitir_cadena(UART3, buff);
	uart_recibir_cadena(UART3, buff, 100);
	/*res = WIFI_verifyResponse(buff);
	if(res == WIFI_ERROR){return res;}*/
	
	glcd_printf("\n%s", buff);

	sprintf(buff, "POST %s HTTP/1.1", url);
	uart_transmitir_cadena(UART3, buff);
	sprintf(buff, "Host: %s", host);
	uart_transmitir_cadena(UART3, buff);
	uart_transmitir_cadena(UART3, "Content-Type: application/json");
	sprintf(buff, "Content-Length: %d", contentLength);
	uart_transmitir_cadena(UART3, buff);
	uart_transmitir_cadena(UART3, "");
	uart_transmitir_cadena(UART3, content);

	for(i = 0; i < 17; i++){
		uart_recibir_cadena(UART3, buff, 100);
		/*res = WIFI_verifyResponse(buff);
		if(res == WIFI_ERROR || res == WIFI_OK){return res;}*/
	
		glcd_printf("\n%s", buff);
	}
	return res;
}

uint8_t WIFI_verifyResponse(char *str){
	uint8_t i = 0;
	if(str && str[0] && str[1]){
		while(str[i + 2]){
			if(memcmp((str + i), "OK", 2) == 0){
				return WIFI_OK;
			}
			i++;
		}

		if(str[2] && str[3] && str[4]){
			i = 0;
			while(str[i + 5]){
				if(memcmp((str + i), "ERROR", 5) == 0){
					return WIFI_ERROR;
				}
				i++;
			}
			
			i = 0;
			while(str[i + 4]){
				if(memcmp((str + i), "FAIL", 4) == 0){
					return WIFI_FAIL;
				}
				i++;
			}
		}
	}
	return WIFI_OTHER;
}
