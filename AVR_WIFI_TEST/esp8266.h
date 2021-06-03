/*
 * esp8266.h
 *
 *  Created on: 3 jun. 2021
 *      Author: Juan Francisco
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#define OK 0
#define ERROR 1

uint8_t WIFI_connectWlan(char *ssid, char *pass);

uint8_t WIFI_sendJSON(char *host, uint16_t port, char *url, char *content);

uint8_t WIFI_verifyResponse(char *str);

#endif /* ESP8266_H_ */
