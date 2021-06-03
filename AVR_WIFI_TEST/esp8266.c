/*
 * esp8266.c
 *
 *  Created on: 3 jun. 2021
 *      Author: Juan Francisco
 */

#include <stdio.h>
#include <string.h>
#include "esp8266.h"
#include "usart.h"

uint8_t WIFI_connectWlan(char *ssid, char *pass){
	char buff[100];
	uint8_t res = 0;

	sprintf(buff, "AT+CWJAP=\"%s\",\"%s\"", ssid, pass);
	USART_TransmitStrCR_LF(buff);
	USART_Receive_UpTo_CR_LF(buff, 100);

	return res;
}

uint8_t WIFI_sendJSON(char *host, uint16_t port, char *url, char *content){
	char buff[100];
	uint8_t hostLength = 0, urlLength = 0, contentLength = 0;
	uint8_t sendSize = 79;

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

	USART_TransmitStrCR_LF("AT+CIPMUX=0");
	USART_Receive_UpTo_CR_LF(buff, 100);

	sprintf(buff, "AT+CIPSTART=\"TCP\",\"%s\",%d", host, port);
	USART_TransmitStrCR_LF(buff);
	USART_Receive_UpTo_CR_LF(buff, 100);

	sprintf(buff, "AT+CIPSEND=%d", sendSize);
	USART_TransmitStrCR_LF(buff);
	USART_Receive_UpTo_CR_LF(buff, 100);

	sprintf(buff, "POST %s HTTP/1.1", url);
	USART_TransmitStrCR_LF(buff);
	sprintf(buff, "Host: %s", host);
	USART_TransmitStrCR_LF(buff);
	USART_TransmitStrCR_LF("Content-Type: application/json");
	sprintf(buff, "Content-Length: %d", contentLength);
	USART_TransmitStrCR_LF(buff);
	USART_TransmitStrCR_LF("");
	USART_TransmitStrCR_LF(content);

	for(uint8_t i = 0; i < 18; i++){
		USART_Receive_UpTo_CR_LF(buff, 100);
	}
	return 0;
}

uint8_t WIFI_verifyResponse(char *str){
	uint8_t i = 0;
	if(str && str[0] && str[1] && str[2] && str[3] && str[4]){
		while(str[i + 2]){
			if(memcmp((str + i), "OK", 2) == 0){
				return 0;
			}
			i++;
		}

		i = 0;
		while(str[i + 5]){
			if(memcmp((str + i), "ERROR", 5) == 0){
				return 1;
			}
			i++;
		}
	}
	return 2;
}
