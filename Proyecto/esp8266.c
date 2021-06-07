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
#include "timer_lpc40xx.h"

uint8_t WIFI_connectWlan(char *ssid, char *pass){
	char buff[100];
	uint8_t res = WIFI_OK;

	// Configuramos al conexión a la red WiFi mediante el siguiente comando
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
	// Medimos los tamaños de las cadenas a enviar
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

	// Seleccionamos el canal de envío
	uart_transmitir_cadena(UART3, "AT+CIPMUX=0");
	uart_recibir_cadena(UART3, buff, 100);
	//res = WIFI_verifyResponse(buff);
	//if(res != WIFI_OK){return res;}
	timer_retardo_ms(TIMER0, 1000);
	
	glcd_printf("\n%s", buff);

	// Iniciamos la conexión TCP, indicando el número exacto de bytes a enviar
	sprintf(buff, "AT+CIPSTART=\"TCP\",\"%s\",%d", host, port);
	uart_transmitir_cadena(UART3, buff);
	uart_recibir_cadena(UART3, buff, 100);
	res = WIFI_verifyResponse(buff);
	if(res == WIFI_ERROR){return res;}
	timer_retardo_ms(TIMER0, 1000);
	
	glcd_printf("\n%s", buff);

	// Comenzamos la transferencia de datos al servidor
	sprintf(buff, "AT+CIPSEND=%d", sendSize);
	uart_transmitir_cadena(UART3, buff);
	uart_recibir_cadena(UART3, buff, 100);
	res = WIFI_verifyResponse(buff);
	if(res != WIFI_OTHER){return res;}
	timer_retardo_ms(TIMER0, 1000);
	
	glcd_printf("\n%s", buff);

	// Enviamos primero las cabeceras HTTP, y luego el JSON a enviar
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
		res = WIFI_verifyResponse(buff);
		if(res != WIFI_OTHER){return res;}
	
		glcd_printf("\n%s", buff);
	}
	return res;
}

uint8_t WIFI_verifyResponse(char *str){
	if(str && str[0] && str[1]){
		if(strSearch(str, "OK", 2)){return WIFI_OK;}

		if(str[2] && str[3]){
			if(strSearch(str, "FAIL", 4)){return WIFI_FAIL;}
			if(strSearch(str, "busy", 4)){return WIFI_BUSY;}
			
			if(str[4]){
				if(strSearch(str, "ERROR", 5)){return WIFI_ERROR;}
			}
		}
	}
	return WIFI_OTHER;
}

uint8_t strSearch(char *str, char *srch, uint8_t size){
	uint8_t i;
	if(str && srch){
		for(i = 0; str[i + size]; i++){
			if(memcmp((str + i), srch, size) == 0){
				return 1;
			}
		}
	}
	return 0;
}
