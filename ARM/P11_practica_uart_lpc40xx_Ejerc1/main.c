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

// main para el ejercicio 1.

int main(void)
{// Declaración de las variables necesarias.
    
	uint32_t joystick, joystick_anterior;
	char dato, buff[100];
    
 // Inicializar la pantalla LCD.
    
	glcd_inicializar();
    
 // Inicializar la UART0:
 // 9600 baudios, datos de 8 bits, sin paridad y un bit de stop.
 // Usar el pin P0[2] para TxD y el pin P0[3] para RxD.
    
	uart_inicializar(UART0, UART_BAUDRATE_9600, UART_BITS_DATOS_8, UART_PARIDAD_NINGUNA, UART_BITS_STOP_1, PUERTO0, PIN2, PUERTO0, PIN3, NULL);
    
 // Inicializar los LEDs.
    
	leds_inicializar();
    
 // Dentro de un bucle "infinito" ...
	joystick_anterior = JOYSTICK_NADA;
	while(TRUE){
		// Leer el joystick.
		// Si está pulsado hacia arriba, enviar el carácter 'A' a través de la UART0.
		// Si está pulsado hacia abajo, enviar el carácter 'B' a través de la UART0.
		// Si está pulsado hacia la izquierda, enviar el carácter 'I' a través de la UART0.
		// Si está pulsado hacia la derecha, enviar el carácter 'D' a través de la UART0.
		joystick = leer_joystick();
		if(joystick != joystick_anterior){
			joystick_anterior = joystick;
			switch(joystick){
				case JOYSTICK_ARRIBA:
					uart_transmitir_dato(UART0, 'A');
					break;
				case JOYSTICK_ABAJO:
					uart_transmitir_dato(UART0, 'B');
					break;
				case JOYSTICK_IZQUIERDA:
					uart_transmitir_dato(UART0, 'I');
					break;
				case JOYSTICK_DERECHA:
					uart_transmitir_dato(UART0, 'D');
					break;
				case JOYSTICK_CENTRO:
					uart_transmitir_cadena(UART0, "Hola mundo!");
					break;
			}
		}
		
		// Si en este momento hay al menos un dato en el buffer de entrada de la
		// UART0 (función uart_hay_dato_disponible).
		// Leer un dato de la UART0 (sacar un dato del buffer de entrada de la UART0).
		// Si el dato es el carácter '1' invertir el estado del LED1. */
		// Si el dato es el carácter '2' invertir el estado del LED2. */
		// Si el dato es el carácter '3' invertir el estado del LED3. */
		// Si el dato es el carácter '4' invertir el estado del LED4. */
		if(uart_hay_dato_disponible(UART0)){
			/*dato = uart_leer_dato(UART0);
			switch(dato){
			case '1':
				led_invertir(LED1);
				break;
			case '2':
				led_invertir(LED2);
				break;
			case '3':
				led_invertir(LED3);
				break;
			case '4':
				led_invertir(LED4);
				break;
			}
			glcd_xprintf(0,0,BLANCO, NEGRO, FONT16X32, "Carácter recibido: %c", dato);*/
			uart_recibir_cadena(UART0, buff, 100);
			glcd_borrar(NEGRO);
			glcd_xprintf(0,0,BLANCO, NEGRO, FONT16X32, "%s", buff);
		}
	}
}
