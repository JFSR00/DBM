/***************************************************************************//**
 * \file    main.c
 * \brief   Función main para la práctica sobre UART.
 */
#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "joystick.h"
#include "leds.h"
#include "error.h"
#include "uart_lpc40xx.h"
#include "timer_lpc40xx.h"
#include "stdlib.h"
#include "stdio.h"
#include "esp8266.h"

// main para el ejercicio 2.

int main(void)
{
	int counter = 0;
	
	glcd_inicializar();
	glcd_borrar(NEGRO);

	uart_inicializar(UART3, UART_BAUDRATE_9600, UART_BITS_DATOS_8, UART_PARIDAD_NINGUNA, UART_BITS_STOP_1, PUERTO0, PIN2, PUERTO0, PIN3, NULL);
	
	timer_inicializar(TIMER0);
	
	glcd_xy_texto(0,0);
	glcd_borrar(NEGRO);
	
	WIFI_connectWlan("iPhone", "Alvaro20");
	//WIFI_connectWlan("WLAN_J3A4", "20200430");

	while(TRUE){
		uint8_t WIFI_sendJSON(char *host, uint16_t port, char *url, char *content);
		glcd_printf("\nContador: %d", counter);
		counter++;
		timer_retardo_ms(TIMER0, 5000);
	}
}
  
    

