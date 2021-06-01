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

// main para el ejercicio 2.

int main(void)
{
	char buff[40];
	
	glcd_inicializar();
	glcd_borrar(NEGRO);
	uart_inicializar(UART2, UART_BAUDRATE_9600, UART_BITS_DATOS_8, UART_PARIDAD_NINGUNA, UART_BITS_STOP_1, PUERTO0, PIN10, PUERTO0, PIN11, NULL);
	
	timer_inicializar(TIMER0);

	while(TRUE){
		glcd_xy_texto(0,0);
		glcd_borrar(NEGRO);
		
		uart_transmitir_cadena(UART0, "AT\n\r");
		uart_recibir_cadena(UART2, buff, 12);
		glcd_printf("%s", buff);
		uart_transmitir_cadena(UART0, "AT\r\n");
		uart_recibir_cadena(UART2, buff, 12);
		glcd_printf("%s", buff);
		timer_retardo_ms(TIMER0, 5000);
	}
}
  
    

