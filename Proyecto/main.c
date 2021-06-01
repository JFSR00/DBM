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
#include "stdlib.h"
#include "stdio.h"

// main para el ejercicio 2.

int main(void)
{ // Declaración de las variables necesarias.

	char buff[40];
	uint32_t dato1, dato2, resultado;

	// Inicializar la pantalla LCD.

	glcd_inicializar();
	glcd_borrar(NEGRO);

	// Inicializar la UART0:
	// 9600 baudios, datos de 8 bits, sin paridad y un bit de stop.
	// Usar el pin P0[2] para TxD y el pin P0[3] para RxD.

	uart_inicializar(UART0, UART_BAUDRATE_9600, UART_BITS_DATOS_8, UART_PARIDAD_NINGUNA, UART_BITS_STOP_1, PUERTO0, PIN2, PUERTO0, PIN3, NULL);

	// Dentro de un bucle "infinito" ...
	while(TRUE){
	 // Borrar la pantalla LCD.
	 glcd_xy_texto(0,0);

	 // Enviar a través de la UART0 un mensaje que indique al usuario que
	 // debe introducir el primer número entero a sumar
	 // (función uart_transmitir_cadena)
			
	 uart_transmitir_cadena(UART0, "Dato 1: ");

	 // Recibir una cadena de caracteres a través de la UART0
	 // (función uart_recibir_cadena).
			
	 uart_recibir_cadena(UART0, buff, 12);
	 glcd_borrar(NEGRO);										// Colocando la función borrar aquí, conservamos el contenido de la pantalla hasta que el usuario empiece la introducción de nuevos operandos
	 glcd_printf("Dato 1: %s\n", buff);
			
	 // Convertir la cadena de caracteres recibida a un valor entero
	 // mediante la función atoi y guardar el resultado en una variable.
	 dato1 = atoi(buff);
			
	 // Enviar a través de la UART0 un mensaje que indique al usuario que
	 // debe introducir el segundo número entero a sumar.
			
	 uart_transmitir_cadena(UART0, "Dato 2: ");

	 // Recibir una cadena de caracteres a través de la UART0.
			
	 uart_recibir_cadena(UART0, buff, 12);
	 glcd_printf("Dato 2: %s\n", buff);
			
	 // Convertir la cadena de caracteres recibida a un valor entero
	 // y guardar el resultado en otra variable.
			
	 dato2 = atoi(buff);
			
	 // Sumar las variables que contienen los números.
			
	 resultado = dato1 + dato2;
			
	 // Transformar el valor de la suma en una cadena de caracteres que la
	 // represente en decimal mediante la función snprintf.
			
	 snprintf (buff, 40, "Suma: %d", resultado);
			
	 // Transmitir a través de la UART0 la cadena con el resultado.
	 uart_transmitir_cadena(UART0, buff);
	 glcd_printf("%s", buff);
	}
}
  
    

