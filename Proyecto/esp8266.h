/*
 * esp8266.h
 *
 *  Created on: 3 jun. 2021
 *      Author: Juan Francisco
 */

#ifndef ESP8266_H_
#define ESP8266_H_

#include <LPC407x_8x_177x_8x.h>

#define WIFI_OK 0
#define WIFI_ERROR 1
#define WIFI_FAIL 2
#define WIFI_BUSY 3
#define WIFI_OTHER 4

// Esta función configura el módulo WiFi para conectarse a la red con el SSID especificado y la contraseña correspondiente
uint8_t WIFI_connectWlan(char *ssid, char *pass);

// Esta función envía la cadena que contiene el JSON especificado al host, puerto y URL también especificados
uint8_t WIFI_sendJSON(char *host, uint16_t port, char *url, char *content);

// Esta función lee la cadena introducida, que se espera que sea una cadena de respuesta del módulo WiFi y devuelve un código en función del contenido de la misma
uint8_t WIFI_verifyResponse(char *str);

// Esta función busca en la primera cadena el contenido de la segunda, especificando el tamaño de la segunda cadena
uint8_t strSearch(char *str, char *srch, uint8_t size);

#endif /* ESP8266_H_ */
